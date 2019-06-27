
#ifndef MCQ_CORRECTION_REQUESTMANAGEMENT_H
#define MCQ_CORRECTION_REQUESTMANAGEMENT_H

#include "../Simple-Web-Server/server_https.hpp"
#include "../Model/DatabaseManager.h"

using SimpleWeb::CaseInsensitiveMultimap;

class RequestManagement {
private:
    DatabaseManager db;
    void loginVerification(const CaseInsensitiveMultimap& headers);
public:
    RequestManagement() = default;
    virtual ~RequestManagement() = default;

    string tokenRequest(const CaseInsensitiveMultimap& parameters);
    string authenticateRequest(const CaseInsensitiveMultimap& headers);
    string promotionRequest(const CaseInsensitiveMultimap& headers);
    string examinationRequest(const CaseInsensitiveMultimap& parameters, const CaseInsensitiveMultimap& headers);
    string studentRequest(const CaseInsensitiveMultimap& parameters, const CaseInsensitiveMultimap& headers);
    string correctionRequest(const CaseInsensitiveMultimap& parameters, const CaseInsensitiveMultimap& headers, int argc, char** argv);
    string correctionPromotionRequest(const CaseInsensitiveMultimap& parameters, const CaseInsensitiveMultimap& headers, int argc, char** argv);
};

#endif //MCQ_CORRECTION_REQUESTMANAGEMENT_H
