
#ifndef MCQ_CORRECTION_HASH_H
#define MCQ_CORRECTION_HASH_H

#include <string>

using std::string;

/// Hash a string using the sha512 hash algorithm.
/// @param input the string to encode
/// @return the string hashed into sha512 format.
string sha512(const string& str);

#endif //MCQ_CORRECTION_HASH_H
