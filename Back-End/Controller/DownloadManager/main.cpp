#include <QCoreApplication>

#include "DownloadManager.h"

int main(int argc, char **argv)
{
    int idPromotion = 1, idStudent = 1;
    QCoreApplication app(argc, argv);
    DownloadManager manager;
    manager.doDownload(idPromotion, idStudent);
    app.exec();
}