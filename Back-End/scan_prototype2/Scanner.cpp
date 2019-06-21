//
// Created by jerem on 19/06/2019.
//

#include "Scanner.h"
#include <cmath>
using std::make_pair;

int findStart(QImage &image) {
    int i = 0;
    bool found = false;
    int place = -1;
    QColor qColor;

    while (!found){
        qColor = image.pixelColor(i, i);
        if (qColor.lightness() < 200) {
            if (tryPlace(image, i, i, 0, 200)){
                place = i;
                found = true;
            }
        }
        i++;
    }
    return place;
}

bool tryPlace(QImage &image, int x, int y, int minLightness, int maxLightness){
    int fill = 0;
    QColor qColor;
    int color;

    for (int i = 0; i<10; i++){
        for (int j = 0; j<10; j++) {
            qColor = image.pixelColor(x + i,y + j);
            color = qColor.lightness();
            if (color > minLightness && color < maxLightness) {
                fill++;
            }
        }
    }
    return fill > 80; // (fill > 80) ? true : false;
}


vector<int> positions(QImage &image, bool orientation){
    int start = findStart(image) + 10; // +10 pour s'assurer de passer sur les bandes
    int y = start;
    bool status = true;
    vector<int> position;
    QColor color;
    int a;
    int b;
    int size = image.width();
    if (orientation){
        size = image.height();
    }

    for (int x = start; x < size ; x++){
        if (!orientation){
            a = x;
            b = y;
        }
        else {
           a = y;
           b = x;
        }
        color = image.pixelColor(a, b);

        if (status) {
            if (color.lightness() > 200){
                if (tryPlace(image, a, b, 200, 400)){
                    status = false;
                }
            }
        }
        else {
            if (color.lightness() < 200) {
                if (tryPlace(image, a, b, 0, 200)) {
                    status = true;
                    position.push_back(x);
                }
            }
        }
    }

    return position;
}

vector<int> oppositePositions (QImage &image, bool orientation){
    int size = image.height();
    if (orientation){
        size = image.width();
    }

    int start = findStart(image);
    int y = size - start - 10;
    vector<int> oppositePositions;
    int a,b;
    QColor color;
    bool status = true;

    if (!orientation){
        size = image.width();
    }
    else { size = image.height(); }

    for (int x = start; x < size ; x++){
        if (!orientation){
            a = x;
            b = y;
        }
        else {
            a = y;
            b = x;
        }

        color = image.pixelColor(a, b);

        if (status) {
            if (color.lightness() > 200){
                if (tryPlace(image, a, b, 200, 400)){
                    status = false;
                }
            }
        }
        else {
            if (color.lightness() < 200) {
                if (tryPlace(image, a, b, 0, 200)) {
                    status = true;
                    oppositePositions.push_back(x);
                }
            }
        }
    }

    return oppositePositions;
}

int getInclination(int firstValue, int secondValue){
    int inclination = (firstValue + secondValue)/2;
    if (inclination < 0){
        inclination = inclination*(-1);
    }
    return inclination;
}

vector<pair <pair <int,int>, pair <int,int>>> boxPositions(QImage &image){
    vector<pair <pair <int,int>, pair <int,int>>> boxPlace;

    vector<int> xies = positions(image);
    vector<int> yies = positions(image, true);

    vector<int> noXies = oppositePositions(image);
    vector<int> noYies = oppositePositions(image, true);

    int correctX;
    int correctY;
    int diff;
    for (int i = 0; i < xies.size(); i++){
        diff = xies[i] - noXies[i];
        diff = (diff < 0) ? -1 : 1;
        correctX = (int)sqrt(xies[i] * getInclination(xies[i], noXies[i])) - diff;

        for (int j = 0; j < yies.size(); j++){
            diff = yies[i] - noYies[i];
            diff = (diff < 0) ? -1 : 1;
            correctY = (int)sqrt(yies[j] * getInclination(yies[j], noYies[j])) - diff;
            boxPlace.emplace_back( make_pair(correctX-5, correctY), make_pair(j-4, i+1) );
        }
    }
    return boxPlace;
}

bool isBoxFilled(const QImage &image, int x, int y){
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

void drawCircle(QImage &image, int x, int y){
    QPainter circle(&image);
    QPen qpen;
    qpen.setWidth(2);
    qpen.setColor(QColor(Qt::red));
    circle.setPen(qpen);
    circle.drawEllipse(x-5, y-5, 40, 40);
}

vector<pair <int,int>> getAnswers(QImage &image, vector<pair <pair <int,int>, pair <int,int>>> boxPosition){
    int x;
    int y;
    int size = (int)boxPosition.size();
    vector<pair <int,int>> answers;
    for (int i = 0; i < size; i++){
        x = boxPosition[i].first.first;
        y = boxPosition[i].first.second;
        if(isBoxFilled(image, x, y)){
            drawCircle(image, x, y);
            answers.emplace_back(  make_pair(boxPosition[i].second.first, boxPosition[i].second.second) );
        }
    }
    //image.save("name.jpg");
    return answers;
}