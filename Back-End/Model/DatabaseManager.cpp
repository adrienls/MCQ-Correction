#include "DatabaseManager.h"
#include <libconfig.h++>
#include <iostream>

using std::stringstream;
using std::exception;
using std::invalid_argument;
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

void DatabaseManager::fetchData(const string& sqlQuery, const ptree& jsonTree){
    try {
        soci::row data;
        soci::statement select = (session->prepare << sqlQuery, soci::into(data));
        select.execute(true);

        do {
            list->addProduct(new Product(product.get<unsigned int>(0), product.get<string>(1), product.get<unsigned int>(2)));
            //cout << product.get<unsigned int>(0) << " " << product.get<std::string>(1) << " " << product.get<unsigned int>(2) << endl;
        } while (selectProduct.fetch());
    }
    catch (const std::exception &e) {
        cerr << "Error: " << e.what() << endl;
    }
}