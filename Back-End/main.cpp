#include "Simple-Web-Server/client_https.hpp"
#include "Simple-Web-Server/server_https.hpp"

// Added for the default_resource example
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>

#include "Simple-Web-Server/crypto.hpp"
#include "Model/DatabaseManager.h"
#include "Controller/base64.h"
#include "Controller/hash.h"
#include "Controller/httpHeaders.h"
#include "Controller/Scan-Analyses/MainScan.h"

using std::shared_ptr;
using std::invalid_argument;
using std::exception;
using std::thread;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

int main(int argc, char** argv) {
    // HTTPS-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpsServer server("server.crt", "server.key");
    server.config.port = 8080;

    server.resource["^/login"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string token;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
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
            *response << validHeaders(request->http_version);
            response->write(token);
        }
        catch(const exception &e){
            *response << invalidHeaders(request->http_version) << "\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };

    server.resource["^/authenticate$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                           shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
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
            login = decode(login);
            password = decode(password);
            string hash = sha512(password);

            unsigned char* randomToken;
            RAND_bytes(randomToken, 30);
            string token = (char*)randomToken;
            db.addToken(token, login);
            *response << validHeaders(request->http_version);
            response->write(token);
        }
        catch(const exception &e){
            *response << invalidHeaders(request->http_version) << "\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };

    server.resource["^/promotion$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                              shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;
            db.fetchPromotions(jsonResponse);
            *response << validHeaders(request->http_version);
            response->write(jsonResponse);
        }
        catch(const exception &e){
            *response << invalidHeaders(request->http_version) << "\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };


    server.resource["^/examination$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
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
            *response << validHeaders(request->http_version);
            response->write(jsonResponse);
        }
        catch(const exception &e){
            *response << invalidHeaders(request->http_version) << "\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
        }
    };

    server.resource["^/student$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                 shared_ptr<HttpsServer::Request> request) {
        try{
            DatabaseManager db;
            string jsonResponse;

            SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
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
            *response << validHeaders(request->http_version);
            response->write(jsonResponse);
        }
        catch(const exception &e){
            *response << invalidHeaders(request->http_version) << "\r\nContent-Length: " << strlen(e.what()) << "\r\n\r\n" << e.what();
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
int main(int argc, char** argv) {

}
 */