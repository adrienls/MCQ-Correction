//
// Created by jerem on 25/06/2019.
//
#include <QImage>
#include <QCoreApplication>
#include "Scanner.h"
#include "MainScan.h"
#include "DownloadManager.h"

void MainScan(int argc, char** argv, int id_student, int id_promotion, vector<pair <int,int>> &answers, QString &stringImage){
    QCoreApplication downloadApp(argc, argv);
    DownloadManager manager;
    manager.doDownload(id_promotion, id_student); // téléchargement de l'image
    downloadApp.exec();

    QImage image("student_answer.jpg");

    Scanner scan(image);
    scan.getAnswers(answers);
    scan.getImageToString(stringImage);
    remove("student_answer.jpg");
}
