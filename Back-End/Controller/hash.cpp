
//taken from https://stackoverflow.com/questions/2262386/generate-sha256-with-openssl-and-c

#include <iostream>
#include <string>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>
#include "hash.h"

using std::stringstream;
using std::hex;
using std::setw;
using std::setfill;

string sha512(const string& str){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA512_CTX sha512;
    SHA512_Init(&sha512);
    SHA512_Update(&sha512, str.c_str(), str.size());
    SHA512_Final(hash, &sha512);
    stringstream ss;
    for(unsigned int i = 0; i < SHA256_DIGEST_LENGTH; i++){
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}