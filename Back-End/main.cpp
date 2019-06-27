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

    server.resource["^/correctionPromotion"]["GET"] = [&](shared_ptr<HttpsServer::Response> response,
                                                          shared_ptr<HttpsServer::Request> request) {
        try{
            RequestManagement rm;
            string jsonResponse = rm.correctionPromotionRequest(request->parse_query_string(), request->header, argc, argv);

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

    server.default_resource["OPTIONS"] = [](shared_ptr<HttpsServer::Response> response, shared_ptr<HttpsServer::Request> request) {
        CaseInsensitiveMultimap header = defaultHeaders();
        header.emplace("Access-Control-Allow-Headers", "*, Authorization");
        header.emplace("Access-Control-Allow-Methods", "GET, POST, OPTIONS");
        response->write(StatusCode::success_ok, header);
    };

    thread server_thread([&server]() {
        // Start server
        server.start();
    });
    server_thread.join();
}

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