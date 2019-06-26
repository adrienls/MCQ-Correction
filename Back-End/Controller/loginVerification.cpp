//
// Created by adrien on 26/06/19.
//

#include "loginVerification.h"
#include "base64.h"
#include "splitString.h"

using std::invalid_argument;

void loginVerification(DatabaseManager& db, const CaseInsensitiveMultimap& headers){
    if(headers.empty()){
        throw invalid_argument("Empty header! 'Authorization' is a required header for this request.");
    }
    string verifHeader;
    for(const auto& value : headers){
        if(value.first == "Authorization"){
            verifHeader = value.second;
        }
    }
    if(verifHeader.empty()){
        throw invalid_argument("Missing header! 'Authorization' is a required header for this request.");
    }

    vector<string> verification = splitString(verifHeader, " ");
    //the header needs to be in the format 'Authorization: Bearer token'

    if(!db.checkToken(verification[1])){
        throw invalid_argument("Wrong token! Please authenticate.");
    }
}