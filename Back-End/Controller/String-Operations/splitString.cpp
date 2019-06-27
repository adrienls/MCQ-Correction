
#include "splitString.h"
#include <boost/algorithm/string.hpp>

using boost::split;
using boost::is_any_of;
using boost::token_compress_on;

vector<string> splitString(const string& input, const string& delimiter){
    vector<string> separatedWords;
    split(separatedWords, input, is_any_of(delimiter), token_compress_on);
    return separatedWords;
}