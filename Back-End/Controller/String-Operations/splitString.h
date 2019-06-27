
// taken from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/

#ifndef MCQ_CORRECTION_SPLITSTRING_H
#define MCQ_CORRECTION_SPLITSTRING_H

#include <string>
#include <vector>

using std::string;
using std::vector;

vector<string> splitString(const string& input, const string& delimiter);

#endif //MCQ_CORRECTION_SPLITSTRING_H
