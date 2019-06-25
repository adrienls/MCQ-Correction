//
// Created by qsvtr on 6/24/19.
//

#include "DownloadManager.h"
#include <QCoreApplication>
using std::invalid_argument;

DownloadManager::DownloadManager()
{
    libconfig::Config config;
    config.readFile("server.cfg");

    if(!config.lookupValue("images.ip", ip_server))
    {
        throw invalid_argument("Error while reading the configuration file. Make sure the information in server.cfg are correct");
    }
    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
}


void DownloadManager::doDownload(const int &idPromotion, const int &idStudent)
{
    QUrl qurl = QString::fromStdString("http://"+ip_server+"/"+std::to_string(idPromotion)+"/"+std::to_string(idStudent)+".jpg");
    QNetworkRequest request(qurl);
    manager.get(request);
}

void DownloadManager::downloadFinished(QNetworkReply *reply)
{
    QUrl url = reply->url();
    if (reply->error()) {
        throw invalid_argument("Download image failed"); //url.toEncoded().constData()
    }
    QFile file("student_answer.jpg");
    if (!file.open(QIODevice::WriteOnly) || !file.write(reply->readAll()))
    {
        throw invalid_argument("Save image failed");
    }

    file.close();
    reply->deleteLater();
    QCoreApplication::instance()->quit();
}

