//
// Created by jerem on 19/06/2019.
//

#ifndef SCAN_PROTOTYPE2_SCANNER_H
#define SCAN_PROTOTYPE2_SCANNER_H


#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QDebug>
#include <vector>
#include <QPainter>
using std::vector;
using std::pair;

class Scanner {
private:
    QImage image;
    int startX;
    int startY;
    bool cornerStartX;
    bool cornerStartY;
public:
    int getStartX() const;
    int getStartY() const;

    virtual ~Scanner(){};
    Scanner(const QImage &image, bool cornerStartX = false, bool cornerStartY = false);

    void findStart(); // Renvoie la coordonée du carré de réference en haut à gauche

    bool tryPlace(int x, int y, int minLightness, int maxLightness);
    // Renvoie true si le carré 10x10 à partir de la coordonée est plus de 80% rempli de la couleur indiquée

    vector<int> positions(bool orientation = false);
    // Renvoie la position en X (orientation = false) de toute les bandes, pour Y (orientation = true).

    vector<int> oppositePositions (bool orientation = false);
// Renvoie la position en X (orientation = false) de toute les bandes du coté opposé, pour Y (orientation = true).

    float getInclination(int firstValue, int secondValue);

    vector<pair <pair <int,int>, pair <int,int>>> boxPositions();
    // Renvoie la position x,y des checkbox (prend en conte l'inclinaison de la page) et renvoie dans la deuxieme paire
    // le numéro de la question avec le numéro de la réponse associée.

    bool isBoxFilled(int x, int y);
    // Renvoie true si la checkBox est au moins 40% remplie

    void drawCircle(int x, int y);
    // Dessine un cercle rouge autour du point indiqué

    vector<pair <int,int>> getAnswers(vector<pair <int,int>> &answers);
    // Renvoie les réponse de l'éleve détectées et dessine une cercle autour de celle-ci.
    // Enregistre ensuite l'image modifée.

    void getImageToString(QString &stringImage);
    QImage getImage() { return this->image; };
};


#endif //SCAN_PROTOTYPE2_SCANNER_H
