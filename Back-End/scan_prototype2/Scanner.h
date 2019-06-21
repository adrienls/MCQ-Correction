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



int findStart(QImage &image); // Renvoie la coordonée du carré de réference en haut à gauche

bool tryPlace(QImage &image, int x, int y, int minLightness, int maxLightness);
// Renvoie true si le carré 10x10 à partir de la coordonée est plus de 80% rempli de la couleur indiquée


vector<int> positions(QImage &image, bool orientation = false);
// Renvoie la position en X (orientation = false) de toute les bandes, pour Y (orientation = true).

vector<int> oppositePositions (QImage &image, bool orientation = false);
// Renvoie la position en X (orientation = false) de toute les bandes du coté opposé, pour Y (orientation = true).

int getInclination(int firstValue, int secondValue);

vector<pair <pair <int,int>, pair <int,int>>> boxPositions(QImage &image);
// Renvoie la position x,y des checkbox (prend en conte l'inclinaison de la page) et renvoie dans la deuxieme paire
// le numéro de la question avec le numéro de la réponse associée.

bool isBoxFilled(const QImage &image, int x, int y);
// Renvoie true si la checkBox est au moins 40% remplie

void drawCircle(QImage &image, int x, int y);
// Dessine un cercle rouge autour du point indiqué

vector<pair <int,int>> getAnswers(QImage &image, vector<pair <pair <int,int>, pair <int,int>>> boxPosition);
// Renvoie les réponse de l'éleve détectées et dessine une cercle autour de celle-ci.
// Enregistre ensuite l'image modifée.



#endif //SCAN_PROTOTYPE2_SCANNER_H