
#ifndef MCQ_CORRECTION_HTTPHEADERS_H
#define MCQ_CORRECTION_HTTPHEADERS_H

#include <string>
#include <sstream>

using std::string;
using std::stringstream;

string validHeaders(const string& http_version){
    stringstream ss;
    ss << "Content-Type: text/plain; charset=utf-8" << std::endl <<
          "Cache-control: no-store, no-cache, must-revalidate\r\n"
          "Pragma: no-cache\r\n";
          //"HTTP/" << http_version << " 200 OK\r\n";
    return ss.str();
}

string invalidHeaders(const string& http_version){
    stringstream ss;
    ss << "HTTP/" << http_version << " 400 Bad Request\r\n";
    return ss.str();
}

#endif //MCQ_CORRECTION_HTTPHEADERS_H
