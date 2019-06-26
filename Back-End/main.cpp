#include <QImage>

#include "Simple-Web-Server/client_https.hpp"
#include "Simple-Web-Server/server_https.hpp"

#include "Simple-Web-Server/crypto.hpp"
#include "Model/DatabaseManager.h"
#include "Controller/base64.h"
#include "Controller/hash.h"
#include "Controller/httpHeaders.h"
#include "Controller/Scan-Analyses/MainScan.h"
#include "Controller/DownloadManager.h"
#include "Controller/token.h"

using std::shared_ptr;
using std::invalid_argument;
using std::exception;
using std::thread;
using std::stringstream;
using std::endl;

using SimpleWeb::StatusCode;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

int main(int argc, char** argv) {
    // HTTPS-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    //HttpsServer server("server.crt", "server.key");
    HttpsServer server("server.crt", "server.key");
    server.config.port = 8080;

    server.resource["^/login$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string token;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need a 'login' parameter for this request.");
            }
            string login;
            for(const auto& value : parameters){
                if(value.first == "login"){
                    login = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'login' is the only valid parameter for this request.");
                }
            }
            db.fetchToken(token, login);
            response->write(StatusCode::success_ok, token, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/authenticate$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                           shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need 'login' and 'password' parameters for this request.");
            }
            string login, password;
            for(const auto& value : parameters){
                if(value.first == "login"){
                    login = value.second;
                }
                else if(value.first == "password"){
                    password = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'login' and 'password' are the only valid parameters for this request.");
                }
            }

            login = decode_base64(login);
            password = decode_base64(password);

            if(!db.checkUser(login, sha512(password))){
                throw invalid_argument("User does not exist!");
            }

            string token = random_string(40);
            db.addToken(token, login);

            response->write(StatusCode::success_ok, login, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/promotion$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                              shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;
            db.fetchPromotions(jsonResponse);
            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };


    server.resource["^/examination$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need 'id_promotion' and 'login_teacher' parameters for this request.");
            }
            string id, login;
            for(const auto& value : parameters){
                if(value.first == "id_promotion"){
                    id = value.second;
                }
                else if(value.first == "login_teacher"){
                    login = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'id_promotion' and 'login_teacher' are the only valid parameters for this request.");
                }
            }
            db.fetchExams(jsonResponse, id, login);
            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/student$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                 shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need a 'id_promotion' parameter for this request.");
            }
            string id;
            for(const auto& value : parameters){
                if(value.first == "id_promotion"){
                    id = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'id_promotion' is the only valid parameter for this request.");
                }
            }

            db.fetchStudents(jsonResponse, id);
            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/correction"]["GET"] = [&](shared_ptr<HttpsServer::Response> response,
                                                  shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need 'id_examination' and 'id_student' parameters for this request.");
            }
            string id_examination, id_student;
            for(const auto& value : parameters){
                if(value.first == "id_examination"){
                    id_examination = value.second;
                }
                else if(value.first == "id_student"){
                    id_student = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'id_examination' and 'id_student' are the only valid parameters for this request.");
                }
            }

            //launch Scan-Analyses
            vector<pair <int,int>> answers;
            string stringImage;
            MainScan(argc, argv , stoi(id_examination), stoi(id_student), answers, stringImage);

            //insert in database
            if (db.NumberResponsesOfStudentsInExamination(id_examination, id_student) == 0){
                db.insertResponses(stoi(id_student), answers);
            }
            //return json
            db.fetchResponses(stringImage, jsonResponse, id_examination, id_student);
            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    // Default GET-example. If no other matches, this anonymous function will be called.
    // Can for instance be used to retrieve an HTML 5 client that uses REST-resources on this server
    server.default_resource["GET"] = [](shared_ptr<HttpsServer::Response> response, shared_ptr<HttpsServer::Request> request) {
        const string& resource = request->path;
        if(resource == "/"){
            response->write(StatusCode::client_error_bad_request, "No resource specified! Please specify a resource with the corresponding parameters.", defaultHeaders());
        }
        else{
            stringstream errorQuery;
            errorQuery << "Wrong query! " << endl << resource << " is not an available resource." << endl;
            response->write(StatusCode::client_error_bad_request, errorQuery.str(), defaultHeaders());
        }
    };

    thread server_thread([&server]() {
        // Start server
        server.start();
    });
    server_thread.join();
}


/*
 *
 * Main pour tester le scanner, tout les includes sont déjà présent en haut du fichier
 *
 */
/*
#include "Controller/Scan-Analyses/MainScan.h"
#include <QImage>
#include "Controller/DownloadManager.h"
int main(int argc, char *argv[])
{
    vector<pair <int,int>> answers;
    QString stringImage;
    MainScan(argc, argv , 1, 4, answers, stringImage);
    std::cerr << stringImage.toStdString() << std::endl;
    for(const auto& val : answers){
        std::cerr << "Question :" << val.first << " ------ Réponse: " << val.second << std::endl;
    }
}
 */