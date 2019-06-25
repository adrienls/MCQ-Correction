//
// Created by qsvtr on 6/24/19.
//

#ifndef QTDOWNLOADER2_DOWNLOADMANAGER_H
#define QTDOWNLOADER2_DOWNLOADMANAGER_H

#include <QFile>
#include <QFileInfo>
#include <QList>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <libconfig.h++>

class DownloadManager: public QObject
{
Q_OBJECT
    QNetworkAccessManager manager;
private:
    std::string ip_server;
public:
    DownloadManager();
    void doDownload(const int &idPromotion, const int &idStudent);

public slots:
    void downloadFinished(QNetworkReply *reply);
};


#endif //QTDOWNLOADER2_DOWNLOADMANAGER_H
