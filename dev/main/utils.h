#ifndef __UTILS_H__
#define __UTILS_H__
#endif

#include <string>
#include <sstream>
#include <vector>

extern const size_t NPOS;
typedef std::vector<std::string> string_vector;
typedef std::pair<std::string,std::string> string_pair;

template<typename Out>
void split(const std::string &s, char delim, Out result);

string_vector split(const std::string &s, char delim);
string_pair strbreak(const std::string &s, char delim, size_t pos=0);
string_pair strrbreak(const std::string &s, char delim, size_t pos=NPOS);

void unencode(const char*,const char*,char*);
