
#include <random>
#include <sstream>
#include "randomString.h"

using std::random_device;
using std::mt19937_64;
using std::uniform_int_distribution;
using std::stringstream;

string randomString(unsigned int size){

    //contains all valid base64 characters
    const string BASE64("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/");

    random_device rd;
    mt19937_64 generator(rd());

    uniform_int_distribution<unsigned short> range(0, 63);
    unsigned short randomIndex;

    stringstream randomString;
    for(unsigned int i = 0; i < size; i++){
        randomIndex = range(generator);
        randomString << BASE64[randomIndex];
    }

    return randomString.str();
}