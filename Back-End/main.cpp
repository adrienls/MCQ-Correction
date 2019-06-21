#include "Simple-Web-Server/client_https.hpp"
#include "Simple-Web-Server/server_https.hpp"

// Added for the json-example
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

// Added for the default_resource example
#include "Simple-Web-Server/crypto.hpp"
#include "Model/DatabaseManager.h"
#include "Controller/base64.h"
#include "Controller/hash.h"
#include <algorithm>
#include <boost/filesystem.hpp>
#include <fstream>
#include <vector>
#include <openssl/sha.h>

using namespace std;
// Added for the json-example:
using namespace boost::property_tree;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;

int main() {
    // HTTPS-server at port 8080 using 1 thread
    // Unless you do more heavy non-threaded processing in the resources,
    // 1 thread is usually faster than several threads
    HttpsServer server("server.crt", "server.key");
    server.config.port = 8080;


    server.resource["^/login"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
        DatabaseManager db;
        string token;

        SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
        string login;
        for(const auto& value : parameters){
            if(value.first == "login_teacher"){
                login = value.second;
            }
            //TODO verif le cas du else et renvoyer erreur
        }

        db.fetchToken(token, login);
        response->write(token);
    };

    server.resource["^/authenticate$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                           shared_ptr<HttpsServer::Request> request) {
        DatabaseManager db;
        string token;

        SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
        string login, password;
        for(const auto& value : parameters){
            if(value.first == "login"){
                login = value.second;
            }
            else if(value.first == "password"){
                password = value.second;
            }
            //TODO verif le cas du else et renvoyer erreur
        }

        login = decode(login);
        password = decode(password);

        string hash = sha512(password);

        db.fetchToken(token, login);
        response->write(token);
    };

    server.resource["^/promotion$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                              shared_ptr<HttpsServer::Request> request) {
        DatabaseManager db;
        string jsonResponse;
        db.fetchPromotions(jsonResponse);
        response->write(jsonResponse);
    };


    server.resource["^/examination$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                shared_ptr<HttpsServer::Request> request) {
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
        }

        db.fetchExams(jsonResponse, id, login);
        response->write(jsonResponse);
    };

    server.resource["^/student$"]["GET"] = [](shared_ptr<HttpsServer::Response> response,
                                                 shared_ptr<HttpsServer::Request> request) {
        DatabaseManager db;
        string jsonResponse;

        SimpleWeb::CaseInsensitiveMultimap parameters = request->parse_query_string();
        string id;
        for(const auto& value : parameters){
            if(value.first == "id_promotion"){
                id = value.second;
            }
        }

        db.fetchStudents(jsonResponse, id);
        response->write(jsonResponse);
    };

    server.on_error = [](shared_ptr<HttpsServer::Request> /*request*/, const SimpleWeb::error_code & /*ec*/) {
        // Handle errors here
        // Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
    };

    thread server_thread([&server]() {
        // Start server
        server.start();
    });

    server_thread.join();
}