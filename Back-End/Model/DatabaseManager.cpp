#include <libconfig.h++>
#include <iostream>
#include "DatabaseManager.h"
#include <vector>

using std::vector;
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
    session = new soci::session(connection.str());
    soci::statement setEncoding = (session->prepare << "SET NAMES utf8");
    setEncoding.execute(true);
}
bool DatabaseManager::checkToken(const string& token){
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "SELECT login FROM teacher WHERE token = :token",
            soci::use(token, "token"),
            soci::into(fields));
    selectFields.execute(true);

    return !fields.get<string>(0).empty();
}
bool DatabaseManager::checkUser(const string& login, const string& password){
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "SELECT login FROM teacher WHERE login = :login AND password = :password",
            soci::use(login, "login"),
            soci::use(password, "password"),
            soci::into(fields));
    selectFields.execute(true);

    return !fields.get<string>(0).empty();
}
void DatabaseManager::addToken(const string& token, const string &login) {
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "UPDATE teacher SET token = :token WHERE login = :login",
            soci::use(token, "token"),
            soci::use(login, "login"),
            soci::into(fields));
    selectFields.execute(true);
}

void DatabaseManager::fetchToken(string& token, const string& login){
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "SELECT token FROM teacher WHERE login = :login",
            soci::use(login, "login"),
            soci::into(fields));
    selectFields.execute(true);

    token = fields.get<string>(0);
    if(token.empty()){
        stringstream error;
        error << "Invalid login: '" << login << "'" << endl;
        throw invalid_argument(error.str());
    }
}
void DatabaseManager::fetchPromotions(string& jsonResponse){
    soci::row fields;
    soci::statement selectFields = (session->prepare << "SELECT id_promotion, name FROM promotion", soci::into(fields));
    selectFields.execute(true);

    stringstream json;
    json << "[";
    do {
        json << "{\"id_promotion\":\"" << to_string(fields.get<int>(0)) << "\", \"name\":\"" << fields.get<string>(1) << "\"}, ";
    }
    while (selectFields.fetch());
    json << "]";

    jsonResponse = json.str();
}
void DatabaseManager::fetchExams(string& jsonResponse, const string& id_promotion, const string& login_teacher){
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "SELECT id_examination, name FROM examination WHERE id_promotion = :id AND login_teacher = :login",
            soci::use(id_promotion, "id"),
            soci::use(login_teacher, "login"),
            soci::into(fields));
    selectFields.execute(true);

    stringstream json;
    json << "[";
    do {
        json << "{\"id_examination\":\"" << to_string(fields.get<int>(0)) << "\", \"name\":\"" << fields.get<string>(1) << "\"}, ";
    }
    while (selectFields.fetch());
    json << "]";

    jsonResponse = json.str();

    if(jsonResponse == "[]"){
        stringstream error;
        error << "Invalid id_promotion: '" << id_promotion << "' and login_teacher: '" << login_teacher <<
        "'. No entry associated to those two parameters." << endl;
        throw invalid_argument(error.str());
    }
}
void DatabaseManager::fetchStudents(string& jsonResponse, const string& id_promotion){
    soci::row fields;
    soci::statement selectFields = (session->prepare <<
            "SELECT id_student, firstname, lastname FROM student WHERE id_promotion = :id",
            soci::use(id_promotion, "id"),
            soci::into(fields));
    selectFields.execute(true);

    stringstream json;
    json << "[";
    do {
        json << "{\"id_student\":\"" << to_string(fields.get<int>(0)) << "\", \"firstname\":\"" << fields.get<string>(1) << "\", \"lastname\":\"" << fields.get<string>(2) << "\"}, ";
    }
    while (selectFields.fetch());
    json << "]";

    jsonResponse = json.str();

    if(jsonResponse == "[]"){
        stringstream error;
        error << "Invalid id_promotion: '" << id_promotion << "'" << ". No entry associated to this parameter." << endl;
        throw invalid_argument(error.str());
    }
}

int DatabaseManager::NumberResponsesOfStudentsInExamination(const string& id_examination, const string& id_student)
{
    int count;
    soci::statement selectFields = (session->prepare << "SELECT COUNT(id_answer) FROM answer JOIN question ON question.id_question = answer.id_question WHERE id_examination = :id_examination AND id_student = :id_student",
            soci::use(id_examination, "id_examination"),
            soci::use(id_student, "id_student"),
            soci::into(count));
    selectFields.execute(true);
    return count;
}

void DatabaseManager::insertResponses(const int &id_student, const std::vector<std::pair<int, int>> &answers)
    {for(const auto& val : answers) {
            soci::row fields;
            soci::statement selectFields = (session->prepare
                    << "INSERT INTO answer(id_student, id_question, value) VALUES (:id_student, :id_question, :value)",
                    soci::use(id_student, "id_student"),
                    soci::use(val.first, "id_question"),
                    soci::use(val.second, "value"),
                    soci::into(fields));
            selectFields.execute(true);
        }
}

void DatabaseManager::fetchResponses(const string&imageB64, string &jsonResponse, const string &id_examination, const string &id_student){

    soci::row fields;
    soci::statement selectFields = (session->prepare << "SELECT answer.id_question, value FROM answer JOIN question ON question.id_question = answer.id_question WHERE question.id_examination = :id_examination AND answer.id_student = :id_student",
            soci::use(id_examination, "id_examination"),
            soci::use(id_student, "id_student"),
            soci::into(fields));
    selectFields.execute(true);

    int id_question = 0, answer = 0, nbresponses = 5;
    vector<bool> answers;
    for (int i = 0; i < nbresponses; i++)
    {
        answers.push_back(false);
    }
    stringstream json;
    int a=0;
    int b=0;
    json << "[{\"image\": \"" << imageB64 << + "\"},";
    do {
        if (id_question == fields.get<int>(0))
        {
            answers[fields.get<int>(1)-1] = true;
            /*if (answer != fields.get<int>(1){
                json << ",\"responses\":\"" << t-o_string(fields.get<int>(1)) << "\"";//<< "\",";
                answer = fields.get<int>(1);
            }*/
        }
        else {
            //inserer answers
            if (a==1){
                for (int i = 0; i < nbresponses; i++){
                    json << ",\"" << i+1 << "\":\"" << answers[i] << "\"";//<< "\",";
                    answers[i] = false;
                }
                a=0;
            }
            if (id_question != 0) {
                json << "},";
            }
            if (a == 0){
                answers[fields.get<int>(1)-1] = true;
            }
            id_question = fields.get<int>(0);
            if (id_question != b+1){
                std::cout << id_question << " : " << b << std::endl;
                json << "{\"id_question\":\"" << b+1 << "\",";
                for (int i = 0; i < nbresponses; i++){
                    json << ",\"" << i+1 << "\":\"" << 0 << "\"";//<< "\",";
                }
                b++;
            }
            json << "{\"id_question\":\"" << to_string(id_question) << "\",";
            a=1;
            b++;
            //json << "\"responses\":\"" << to_string(fields.get<int>(1)) << "\"";
            //answer = 0;
        }
    }
    while (selectFields.fetch());
    for (int i = 0; i < nbresponses; i++){
        json << ",\"" << i+1 << "\":\"" << answers[i] << "\"";//<< "\",";
        answers[i] = false;
    }
    json << "}]";

    jsonResponse = json.str();

    if(jsonResponse == "[]"){
        stringstream error;
        error << "Invalid id_examination: '" << id_examination << "' and id_student: '" << id_student <<
              "'. No entry associated to those two parameters." << endl;
        throw invalid_argument(error.str());
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
            i++;
        }
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}*/