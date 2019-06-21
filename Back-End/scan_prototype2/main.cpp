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
    QPixmap image("images/1/5.jpg");


    QImage im = image.toImage().convertToFormat(QImage::Format_ARGB32);
    QImage imageCreate(image.width(), image.height(), QImage::Format(QImage::Format_ARGB32));

    // phase de test
    

    QPixmap newImage = QPixmap::fromImage(im);
    // display
    QGraphicsPixmapItem item(newImage);
    scene.addItem(&item);
    view.show();
    return a.exec();
}