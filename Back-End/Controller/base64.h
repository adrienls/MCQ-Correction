
#ifndef MCQ_CORRECTION_BASE64_H
#define MCQ_CORRECTION_BASE64_H

#include <string>
using std::string;

/// Encode a string into Base64 format.
/// @param input the string to encode
/// @return the string encoded into base64 format.
string encode_base64(const string& input);

/// Decode a string from Base64 format.
/// @param input the string to decode
/// @return the decoded string.
string decode_base64(const string& input);

#endif //MCQ_CORRECTION_BASE64_H
