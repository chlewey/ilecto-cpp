#include "ilecto_str.h"

namespace il {
const string nullstr("");
string emptystr("");
const size_t npos = std::string::npos;
const char* spaces = "\t\n\f\v\r ";
	
string& string::ltrim(const char*s) {
	size_t pos = find_first_not_of(s);
	if(pos!=npos)
		erase(0,pos);
	else
		clear();
	return *this;
}

string& string::ltrim(const char*s, size_t n) {
	size_t pos = find_first_not_of(s,0,n);
	if(pos!=npos)
		erase(0,pos);
	else
		clear();
	return *this;
}

string& string::ltrim(char c) {
	size_t pos = find_first_not_of(c);
	if(pos!=npos)
		erase(0,pos);
	else
		clear();
	return *this;
}

string& string::rtrim(const char*s) {
	size_t pos = find_last_not_of(s);
	if(pos!=npos)
		erase(pos+1);
	else
		clear();
	return *this;
}

string& string::rtrim(const char*s, size_t n) {
	size_t pos = find_last_not_of(s,npos,n);
	if(pos!=npos)
		erase(pos+1);
	else
		clear();
	return *this;
}

string& string::rtrim(char c) {
	size_t pos = find_last_not_of(c);
	if(pos!=npos)
		erase(pos+1);
	else
		clear();
	return *this;
}

string& string::url_encode() {
}

char hex2char(const string s) {
	int x;
	std::stringstream ss;
	ss << std::hex << s.substr(0,2);
	ss >> x;
	return x;
}

string& string::url_decode() {
	for(size_t pos = find('+'); pos != npos; pos = find('+',pos))
		replace(pos,1," ");
	for(size_t pos = find('%'); pos != npos; pos = find('+',pos)) {
		replace(pos,3,string(hex2char(substr(pos+1))));
	}
}

string& string::xml_escape() {
}

string& string::xml_unescape() {
}

string& string::html_escape() {
}

string& string::html_unescape() {
}

template<typename Out>
void string::split(char c, Out result) const {
    std::stringstream ss;
    ss.str(*this);
    std::string item;
    while (std::getline(ss, item, c)) {
        *(result++) = item;
    }
}

string_vector string::split(char c) const {
    string_vector elems;
    split(c, std::back_inserter(elems));
    return elems;
}

string_pair string::split_first(char c, size_t pos) const {
	size_t n = find(c,pos);
	if(n==npos) return string_pair(*this, "");
	return string_pair( substr(0,n), substr(n+1) );
}

string_pair string::split_last(char c, size_t pos) const {
	size_t n = rfind(c,pos);
	if(n==npos) return string_pair("", *this);
	return string_pair( substr(0,n), substr(n+1) );
}


}
