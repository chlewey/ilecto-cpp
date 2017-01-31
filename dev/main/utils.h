#ifndef __UTILS_H__
#define __UTILS_H__

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

void unencode(char*,const char*,size_t n=NPOS);

extern const std::string str_spaces;
std::string&ltrim(std::string&src,const std::string&chars=str_spaces);
std::string&rtrim(std::string&src,const std::string&chars=str_spaces);
inline std::string&trim(std::string&src,const std::string&chars=str_spaces) { return ltrim(rtrim(src,chars),chars); }
inline std::string&cltrim(const std::string&src,const std::string&chars=str_spaces) { std::string*sp=new std::string(src); return ltrim(*sp,chars); }
inline std::string&crtrim(const std::string&src,const std::string&chars=str_spaces) { std::string*sp=new std::string(src); return rtrim(*sp,chars); }
inline std::string&ctrim(const std::string&src,const std::string&chars=str_spaces) { std::string*sp=new std::string(src); return trim(*sp,chars); }

#endif
