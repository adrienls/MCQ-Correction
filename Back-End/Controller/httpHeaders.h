
#ifndef MCQ_CORRECTION_HTTPHEADERS_H
#define MCQ_CORRECTION_HTTPHEADERS_H

#include "../Simple-Web-Server/server_https.hpp"

using SimpleWeb::CaseInsensitiveMultimap;

CaseInsensitiveMultimap defaultHeaders(){
    CaseInsensitiveMultimap header;
    header.emplace("Content-Type", "text/plain; charset=utf-8");
    header.emplace("Cache-control", "no-store, no-cache, must-revalidate");
    header.emplace("Pragma", "no-cache");
    header.emplace("Access-Control-Allow-Credentials", "true");
    header.emplace("Access-Control-Allow-Origin", "https://localhost");
    //Solves the Same-origin policy issue
    return header;
}

#endif //MCQ_CORRECTION_HTTPHEADERS_H
