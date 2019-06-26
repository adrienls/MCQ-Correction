
#ifndef MCQ_CORRECTION_LOGINVERIFICATION_H
#define MCQ_CORRECTION_LOGINVERIFICATION_H

#include "../Simple-Web-Server/server_https.hpp"
#include "../Model/DatabaseManager.h"

using SimpleWeb::CaseInsensitiveMultimap;

void loginVerification(DatabaseManager& db, const CaseInsensitiveMultimap& headers);

#endif //MCQ_CORRECTION_LOGINVERIFICATION_H
