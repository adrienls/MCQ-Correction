//
// Created by jerem on 19/06/2019.
//

#include "Scanner.h"
#include <libconfig.h++>
#include <QPen>
#include <QByteArray>
#include <QBuffer>

using std::invalid_argument;
using std::make_pair;

void Scanner::findStart() {
    int x;
    int y;
    if (!cornerStartX){
        x = 0;
    }
    else { x = image.width() - 1; }

    if (!cornerStartY){
        y = 0;
    }
    else { y = image.height() - 1; }

    bool found = false;
    int placeX = -1;
    int placeY = -1;
    QColor qColor;

    while (!found){
        qColor = image.pixelColor(x, y);
        if (qColor.lightness() < 200) {
            if (tryPlace(x, y, 0, 200)){
                placeX = x;
                placeY = y;
                found = true;
            }
        }
        if (!cornerStartX){
            x++;
        }
        else { x--; }

        if (!cornerStartY){
            y++;
        }
        else { y--; }
    }
    int fixX;
    int fixY;
    if (!cornerStartX){ fixX = 30; }
    else { fixX = -30; }

    if (!cornerStartY){ fixY = 30; }
    else { fixY = -30; }

    this->startX = placeX + fixX;
    this->startY = placeY + fixY;
}

bool Scanner::tryPlace(int x, int y, int minLightness, int maxLightness){
    int fill = 0;
    QColor qColor;
    int color;

    for (int i = 0; i<10; i++){
        for (int j = 0; j<10; j++) {
            if (!cornerStartX){
                if (!cornerStartY){
                    qColor = image.pixelColor(x + i,y + j);
                }
                else { qColor = image.pixelColor(x + i,y - j);}
            }
            else {
                if (!cornerStartY){
                    qColor = image.pixelColor(x - i,y + j);
                }
                else { qColor = image.pixelColor(x - i,y - j);}
            }

            color = qColor.lightness();
            if (color > minLightness && color < maxLightness) {
                fill++;
            }
        }
    }
    return fill > 80; // (fill > 80) ? true : false;
}


vector<int> Scanner::positions(bool orientation){
    bool status = true;
    vector<int> position;
    QColor color;

    int size = image.width();
    int iteration = startX;
    if (orientation){
        size = image.height();
        iteration = startY;
    }

    int y = startY;
    int x = startX;
    bool dodgeFirstSquare = true;

    while(iteration < size && iteration > 0){ //traversage de l'image
        color = image.pixelColor(x, y);
        if (status) {
            if (color.lightness() > 200){
                if (tryPlace(x, y, 200, 400)){
                    if (!dodgeFirstSquare) {
                        if (!orientation && cornerStartX) {
                            position.push_back(x);
                        }
                        if (orientation && cornerStartY) {
                            position.push_back(y);
                        }
                    }
                    else { dodgeFirstSquare = false; }
                    status = false;
                }
            }
        }
        else {
            if (color.lightness() < 200) {
                if (tryPlace(x, y, 0, 200)) {
                    status = true;
                    if (!orientation && !cornerStartX){
                        position.push_back(x);
                    }
                    if (orientation && !cornerStartY){
                        position.push_back(y);
                    }
                }
            }
        }

        if (!orientation){
            if(!cornerStartX){ x++; iteration++;}
            else { x--; iteration--;}
        }
        else {
            if(!cornerStartY){ y++; iteration++;}
            else { y--;iteration--; }
        }
    }

    return position;
}

vector<int> Scanner::oppositePositions (bool orientation){
    int size;
    int x;
    int y;
    int iteration;
    if (!orientation) {
        size = image.height();
        y = size - startY;
        x = startX;
        iteration = startX;
    }
    else {
        size = image.width();
        y = startY;
        x = size - startX;
        if ( cornerStartX && cornerStartY ){ x += 10; }
        iteration = startY;
    }

    vector<int> oppositePositions;
    QColor color;
    bool status = true;
    bool dodgeFirstSquare = true;

    if (!orientation){
        size = image.width();
    }
    else { size = image.height(); }

    while (iteration < size && iteration > 0){
        color = image.pixelColor(x, y);

        if (status) {
            if (color.lightness() > 200){
                if (tryPlace(x, y, 200, 400)){
                    if (!dodgeFirstSquare) {
                        if (!orientation && cornerStartX) {
                            oppositePositions.push_back(x);
                        }
                        if (orientation && cornerStartY) {
                            oppositePositions.push_back(y);
                        }
                    }
                    else { dodgeFirstSquare = false; }
                    status = false;
                }
            }
        }
        else {
            if (color.lightness() < 200) {
                if (tryPlace(x, y, 0, 200)) {
                    status = true;
                    if (!orientation && !cornerStartX){
                        oppositePositions.push_back(x);
                    }
                    if (orientation && !cornerStartY){
                        oppositePositions.push_back(y);
                    }
                }
            }
        }

        if (!orientation){
            if(!cornerStartX){ x++; iteration++;}
            else { x--; iteration--;}
        }
        else {
            if(!cornerStartY){ y++; iteration++;}
            else { y--; iteration--; }
        }
    }

    return oppositePositions;
}

float Scanner::getInclination(int firstValue, int secondValue){
    float inclination = (float)secondValue/(float)firstValue;
    return inclination;
}

vector<pair <pair <int,int>, pair <int,int>>> Scanner::boxPositions(){
    vector<pair <pair <int,int>, pair <int,int>>> boxPlace;

    vector<int> xies = positions();
    vector<int> yies = positions(true);

    vector<int> noXies = oppositePositions();
    vector<int> noYies = oppositePositions(true);
    int sizeY = (int)yies.size();
    int sizeX = (int)xies.size()/2;
    int questionNumber;
    int questionNumber2;
    int answerNumber;
    for (int i = 0; i < sizeY; i++){
        for (int j = 0; j < sizeX; j++){
            if (!cornerStartX){
                answerNumber = j + 1;
                if (!cornerStartY) {
                    questionNumber = i - 4;
                    questionNumber2 = i - 4 + sizeY;
                }
                if (cornerStartY){
                    questionNumber = sizeY - i - 5;
                    questionNumber2 = sizeY - i - 5 + sizeY;
                }
            }
            if (cornerStartX){
                answerNumber = sizeX - j;
                if (!cornerStartY){
                    questionNumber = i - 4  + sizeY;
                    questionNumber2 = i - 4;
                }
                if(cornerStartY){
                    questionNumber = sizeY - i - 5  + sizeY;
                    questionNumber2 = sizeY - i - 5;
                }
            }
            boxPlace.emplace_back( make_pair(xies[j]-6, yies[i]), make_pair(questionNumber, answerNumber) );
            boxPlace.emplace_back( make_pair(xies[sizeX + j]-6, yies[i]), make_pair(questionNumber2, answerNumber) );
        }
    }
    return boxPlace;
}

bool Scanner::isBoxFilled(int x, int y){
    QColor color;
    int fill = 0;
    for (int i = 0; i < 25; i++){
        for (int j = 0; j < 25; j++){
            color = image.pixelColor(x + i,y + j);
            if (color.lightness() < 200) {
                fill++;
            }
        }
    }
    return fill > 250;
}

void Scanner::drawCircle(int x, int y){
    QPainter circle(&image);
    QPen qpen;
    qpen.setWidth(3);
    qpen.setColor(QColor(Qt::red));
    circle.setPen(qpen);
    circle.drawEllipse(x-6, y-6, 40, 40);
}

vector<pair <int,int>> Scanner::getAnswers(vector<pair <int,int>> &answers){
    vector<pair <pair <int,int>, pair <int,int>>> boxPosition = boxPositions();
    int x;
    int y;
    int size = (int)boxPosition.size();
    for (int i = 0; i < size; i++){
        x = boxPosition[i].first.first;
        y = boxPosition[i].first.second;
        if(isBoxFilled(x, y)){
            drawCircle(x, y);
            answers.emplace_back(  make_pair(boxPosition[i].second.first, boxPosition[i].second.second) );
        }
    }
    return answers;
}

Scanner::Scanner(const QImage &image, bool cornerStartX, bool cornerStartY) : image(image), cornerStartX(cornerStartX), cornerStartY(cornerStartY) {
    libconfig::Config config;
    config.readFile("server.cfg");

    if(!config.lookupValue("scan.startCorner.right", cornerStartX) || !config.lookupValue("scan.startCorner.bottom", cornerStartY))
    {
        throw invalid_argument("Error while reading the configuration file. Make sure the information in server.cfg are correct");
    }
    findStart();
}

int Scanner::getStartX() const {
    return startX;
}

int Scanner::getStartY() const {
    return startY;
}

void Scanner::getImageToString(std::string &stringImage){
    QBuffer buffer;
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "JPG");
    QByteArray const encoded = buffer.data().toBase64();
    stringImage = encoded.toStdString();

    //QByteArray arr = qCompress(buffer.buffer(),5);
    //stringImage = QString(arr);
}
