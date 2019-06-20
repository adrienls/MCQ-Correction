//
// Created by adrien on 19/06/19.
//

#ifndef MCQ_CORRECTION_DATABASEMANAGER_H
#define MCQ_CORRECTION_DATABASEMANAGER_H

#include <soci.h>
#include <soci-mysql.h>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using std::string;
using boost::property_tree::ptree;

class DatabaseManager {
private:
    string ip;
    string db;
    string user;
    string password;
    soci::session* session = nullptr;
public:
    DatabaseManager();
    ~DatabaseManager(){
        disconnect();
        delete session;
    }

    const string &getIp() const {
        return ip;
    }
    const string &getDb() const {
        return db;
    }
    const string &getUser() const {
        return user;
    }
    const string &getPassword() const {
        return password;
    }

    void connect();
    void disconnect(){
        if(session!= nullptr){
            session->close();
        }
    }
    void fetchData(const string& sqlQuery, const ptree& jsonTree);
};


#endif //MCQ_CORRECTION_DATABASEMANAGER_H
