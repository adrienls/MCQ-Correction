#include <iostream>
#include <QApplication>
#include <QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QDebug>
#include <QCoreApplication>
#include <QtWidgets/qapplication.h>

#include "Scanner.h"
#include "MainScan.h"
#include "../DownloadManager/DownloadManager.h"

void MainScan(int argc, char** argv, int id_student, int id_promotion, vector<pair <int,int>> &answers, QString &stringImage){
    QApplication a(argc, argv);
    QGraphicsScene scene;
    QGraphicsView view(&scene);

    DownloadManager manager;
    //manager.doDownload(idPromotion, idStudent); // téléchargement de l'image

    QPixmap image("../DownloadManager/student_answer.jpg");

    QImage im = image.toImage().convertToFormat(QImage::Format_ARGB32);
    QImage imageCreate(image.width(), image.height(), QImage::Format(QImage::Format_ARGB32));

    Scanner scan(im);
    //scan.getAnswers(&answers);
    //scan.im
    QPixmap newImage = QPixmap::fromImage(scan.getImage());
    // display
    QGraphicsPixmapItem item(newImage);
    scene.addItem(&item);
    view.show();
    a.exec();
}
