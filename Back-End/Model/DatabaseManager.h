
#ifndef MCQ_CORRECTION_DATABASEMANAGER_H
#define MCQ_CORRECTION_DATABASEMANAGER_H

#include <soci.h>
#include <soci-mysql.h>
#include <string>
#include <QtCore/QByteArray>

using std::string;

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

    bool checkUser(const string& login, const string& password);
    void addToken(const string& token, const string& login);

    //void fetchData(const map<string, string>& fields, const string& table, const map<string, string>& where = {});
    void fetchToken(string& token, const string& login_teacher);
    void fetchPromotions(string& jsonResponse);
    void fetchExams(string& jsonResponse, const string& id_promotion, const string& login_teacher);
    void fetchStudents(string& jsonResponse, const string& id_promotion);
    int NumberResponsesOfStudentsInExamination(const string& id_examination, const string& id_student);
    void insertResponses(const int &id_student, const std::vector<std::pair<int, int>> &answers);
    void fetchResponses(const string& image, string &jsonResponse, const string &id_examination, const string &id_student);
};

#endif //MCQ_CORRECTION_DATABASEMANAGER_H
