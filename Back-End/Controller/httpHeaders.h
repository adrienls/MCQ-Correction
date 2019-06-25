
#ifndef MCQ_CORRECTION_HTTPHEADERS_H
#define MCQ_CORRECTION_HTTPHEADERS_H

#include "../Simple-Web-Server/server_https.hpp"

using SimpleWeb::CaseInsensitiveMultimap;
using std::to_string;

CaseInsensitiveMultimap defaultHeaders(){
    CaseInsensitiveMultimap header;
    header.emplace("Content-Type", "text/plain; charset=utf-8");
    header.emplace("Cache-control", "no-store, no-cache, must-revalidate");
    header.emplace("Pragma", "no-cache");
    return header;
}

#endif //MCQ_CORRECTION_HTTPHEADERS_H
