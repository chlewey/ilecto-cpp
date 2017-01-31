
#include "utils.h"

const size_t NPOS = std::string::npos;

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

string_vector split(const std::string &s, char delim) {
    string_vector elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}

string_pair strbreak(const std::string &s, char delim, size_t pos) {
	size_t n = s.find(delim,pos);
	if(n==NPOS) return string_pair(s, "");
	return string_pair( s.substr(0,n), s.substr(n+1) );
}

string_pair strrbreak(const std::string &s, char delim, size_t pos) {
	size_t n = s.rfind(delim,pos);
	if(n==NPOS) return string_pair("", s);
	return string_pair( s.substr(0,n), s.substr(n+1) );
}

void unencode(char *dest,const char *src,size_t n) {
	size_t i=0,j=0;
	for(; i<n && j<n && *(src+i); i++, j++)
		if(*(src+i) == '+')
			*(dest+j) = ' ';
		else if(*(src+i) == '%') {
			int code;
			if(sscanf(src+i+1, "%2x", &code) != 1) code = '?';
			*(dest+j) = code;
			i+=2;
		} else
			*(dest+j) = *(src+i);
	*(dest+j) = '\0';
}

const std::string str_spaces(" \t\f\v\r\n");

std::string& rtrim(std::string&src,const std::string&chars) {
	size_t pos = src.find_last_not_of(chars);
	if(pos!=NPOS)
		src.erase(pos+1);
	else
		src.clear();
	return src;
}

std::string& ltrim(std::string&src,const std::string&chars) {
	size_t pos = src.find_first_not_of(chars);
	if(pos!=NPOS)
		src.erase(0,pos);
	else
		src.clear();
	return src;
}


