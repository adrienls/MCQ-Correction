#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QDebug>

#include "Scanner.h"
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    QPixmap image("images/1/9.jpg");


    QImage im = image.toImage().convertToFormat(QImage::Format_ARGB32);
    QImage imageCreate(image.width(), image.height(), QImage::Format(QImage::Format_ARGB32));

    // phase de test
    vector<pair<int,int>> boxPosition = boxPositions(im);
    int x;
    int y;
    for (int i = 0; i < boxPosition.size(); i++){
        x = boxPosition[i].first;
        y = boxPosition[i].second;
        if(isBoxFilled(im, x, y)){
            drawCircle(im, x-5, y-5);
        }
    }


    QPixmap newImage = QPixmap::fromImage(im);
    // display
    QGraphicsPixmapItem item(newImage);
    scene.addItem(&item);
    view.show();
    return a.exec();
}