#include <libconfig.h++>
#include <iostream>
#include "DatabaseManager.h"

using std::stringstream;
using std::exception;
using std::invalid_argument;
using std::to_string;
using std::cerr;
using std::endl;

DatabaseManager::DatabaseManager() {
    libconfig::Config config;
    config.readFile("server.cfg");

    if(!config.lookupValue("database.ip", ip)
        || !config.lookupValue("database.db", db)
        || !config.lookupValue("database.user", user)
        || !config.lookupValue("database.password", password))
    {
        throw invalid_argument("Error while reading the configuration file. Make sure the information in server.cfg are correct");
    }
    connect();
}
void DatabaseManager::connect() {
    stringstream connection;
    connection << "mysql://db=" << db << " host=" << ip << " user=" << user <<  " password='" << password << "'";
    try {
        session = new soci::session(connection.str());
        soci::statement setEncoding = (session->prepare << "SET NAMES utf8");
        setEncoding.execute(true);
    }
    catch (const exception &e) {
        cerr << "Error: " << e.what() << endl;
    }

}

void DatabaseManager::fetchToken(string& token, const string& login){
    try {
        soci::row fields;
        soci::statement selectFields = (session->prepare <<
                "SELECT token FROM teacher WHERE login = :login",
                soci::use(login, "login"),
                soci::into(fields));
        selectFields.execute(true);

        token = fields.get<string>(0);
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}
void DatabaseManager::fetchPromotions(string& jsonResponse){
    try {
        soci::row fields;
        soci::statement selectFields = (session->prepare << "SELECT id_promotion, name FROM promotion", soci::into(fields));
        selectFields.execute(true);

        stringstream json;
        json << "{";
        do {
            json << "{id_promotion:" << to_string(fields.get<int>(0)) << ", name:" << fields.get<string>(1) << "}, ";
        } while (selectFields.fetch());
        json << "}";

        jsonResponse = json.str();
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}
void DatabaseManager::fetchExams(string& jsonResponse, const string& id_promotion, const string& login_teacher){
    try {
        soci::row fields;
        soci::statement selectFields = (session->prepare <<
                "SELECT id_examination, name FROM examination WHERE id_promotion = :id AND login_teacher = :login",
                soci::use(id_promotion, "id"),
                soci::use(login_teacher, "login"),
                soci::into(fields));
        selectFields.execute(true);

        stringstream json;
        json << "{";
        do {
            json << "{id_examination:" << to_string(fields.get<int>(0)) << ", name:" << fields.get<string>(1) << "}, ";
        } while (selectFields.fetch());
        json << "}";

        jsonResponse = json.str();
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}
void DatabaseManager::fetchStudents(string& jsonResponse, const string& id_promotion){
    try {
        soci::row fields;
        soci::statement selectFields = (session->prepare <<
                "SELECT id_student, firstname, lastname FROM student WHERE id_promotion = :id",
                soci::use(id_promotion, "id"),
                soci::into(fields));
        selectFields.execute(true);

        stringstream json;
        json << "{";
        do {
            json << "{id_student:" << to_string(fields.get<int>(0)) << ", firstname:" << fields.get<string>(1) << ", lastname:" << fields.get<string>(2) << "}, ";
        } while (selectFields.fetch());
        json << "}";

        jsonResponse = json.str();
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}

/*void DatabaseManager::fetchData(const map<string, string>& fields, const string& table, const map<string, string>& where){
    try {
        stringstream query;
        query << "SELECT ";
        for(const auto& value : fields){
            query << value.first;
            auto it = fields.end();
            it--;
            if(value != (*it)){
                query << ", ";
                //add a separator if the field is not the last one to be retrieved
            }
        }
        query << " FROM " << table;
        if(!where.empty()){
            query << " WHERE ";
            for(const auto& value : where){
                query << value.first << " = " << value.second;
                if(value != (*fields.end())){
                    query << " AND ";
                    //add a separator if the field is not the last one
                }
            }
        }

        soci::row data;
        soci::statement select = (session->prepare << query.str(), soci::into(data));
        select.execute(true);

        if(fields.size() != data.size()){
            throw invalid_argument("Wrong query size!");
        }
        unsigned int i = 0;
        for(auto value : fields){
            value.second = data.get<string>(i);
            //TODO forcer l'enregistement des données en string
            i++;
        }
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}*/