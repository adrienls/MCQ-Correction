
#include "base64.h"
#include <QByteArray>

string encode_base64(const string& input){
    QByteArray base64 = QByteArray::fromStdString(input);
    return base64.toBase64().toStdString();
}

string decode_base64(const string& input){
    QByteArray base64 = QByteArray::fromStdString(input);
    return QByteArray::fromBase64(base64).toStdString();
}