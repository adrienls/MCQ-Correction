#include "Simple-Web-Server/client_https.hpp"
#include "Simple-Web-Server/server_https.hpp"

#include "Simple-Web-Server/crypto.hpp"
#include "Controller/httpHeaders.h"
#include "Controller/RequestManagement.h"

using std::shared_ptr;
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

    server.resource["^/token"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string token = rm.tokenRequest(request->parse_query_string());

            response->write(StatusCode::success_ok, token, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/authenticate$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                           shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string token = rm.authenticateRequest(request->header);

            response->write(StatusCode::success_ok, token, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/promotion$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                              shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string jsonResponse = rm.promotionRequest(request->header);

            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/examination$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string jsonResponse = rm.examinationRequest(request->parse_query_string(), request->header);

            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/student$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                 shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string jsonResponse = rm.studentRequest(request->parse_query_string(), request->header);

            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
        }
    };

    server.resource["^/correction$"]["GET"] = [&](shared_ptr<HttpsServer::Response> response,
                                                  shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string jsonResponse = rm.correctionRequest(request->parse_query_string(), request->header, argc, argv);

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

    server.resource["^/correctionPromotion"]["GET"] = [&](shared_ptr<HttpsServer::Response> response,
                                                          shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
            if(parameters.empty()){
                throw invalid_argument("Empty Parameter! You need 'id_examination' and 'id_promotion' parameters for this request.");
            }
            string id_examination, id_promotion;
            for(const auto& value : parameters){
                if(value.first == "id_examination"){
                    id_examination = value.second;
                }
                else if(value.first == "id_promotion"){
                    id_promotion = value.second;
                }
                else{
                    throw invalid_argument("Wrong Parameter! 'id_examination' and 'id_promotion' are the only valid parameters for this request.");
                }
            }

            vector <int> students = db.getStudentsOfPromotions(id_promotion);
            for (int i=0; i < students.size(); i++){
                vector<pair <int,int>> answers;
                string stringImage;
                MainScan(argc, argv , stoi(id_examination), students[i], answers, stringImage);

                //insert in database
                if (db.NumberResponsesOfStudentsInExamination(id_examination, to_string(students[i])) == 0){
                    db.insertResponses(students[i], answers);
                }
            }
            response->write(StatusCode::success_ok, jsonResponse, defaultHeaders());
        }
        catch(const exception &e){
            response->write(StatusCode::client_error_bad_request, e.what(), defaultHeaders());
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