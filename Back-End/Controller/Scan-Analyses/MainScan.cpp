
#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QDebug>
#include "Scanner.h"
#include "MainScan.h"

vector<pair <int,int>> MainScan(int argc, char** argv, int id_student, int id_promotion){
    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);
    //QPixmap image("img/1/5.jpg");
    QPixmap image("img/hautGauche.jpg");
    //QPixmap image("img/basGauche.jpg");
    //QPixmap image("img/hautDroite.jpg");
    //QPixmap image("img/basDroite.jpg");

    QImage im = image.toImage().convertToFormat(QImage::Format_ARGB32);
    QImage imageCreate(image.width(), image.height(), QImage::Format(QImage::Format_ARGB32));

    // phase de test
    Scanner scan(im);
    //vector<int> posx = scan.oppositePositions(true);
    vector<pair <pair <int,int>, pair <int,int>>> posss = scan.boxPositions();
    vector<pair <int,int>> pos = scan.getAnswers(posss);

    // debug

    /*for (int i = 0; i < posx.size(); i++){
        //scan.debugImage(scan.getStartX(), posx[i]);
        //scan.debugImage(posx[i], scan.getStartY());

        //scan.debugImage(posx[i], im.height() - scan.getStartY());
        //scan.debugImage( im.width() - scan.getStartX(), posx[i]);
        cout << "x: " << im.height() - scan.getStartY() << ", Y : " << posx[i] << endl;
    }
    cout << "startx: " << scan.getStartX() << ", startY : " << scan.getStartY() << endl;
    cout << "maxwidth: " << im.width() << ", maxheight : " << im.height() << endl;
    cout << posx.size() << endl;*/

    QPixmap newImage = QPixmap::fromImage(scan.getImage());
    // display
    QGraphicsPixmapItem item(newImage);
    scene.addItem(&item);
    view.show();
    a.exec();
}