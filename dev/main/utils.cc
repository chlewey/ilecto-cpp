
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

void unencode(const char *src, const char *last, char *dest) {
	for(; src != last; src++, dest++)
		if(*src == '+')
			*dest = ' ';
		else if(*src == '%') {
			int code;
			if(sscanf(src+1, "%2x", &code) != 1) code = '?';
			*dest = code;
			src +=2;
		} else
			*dest = *src;
	*dest = '\0';
}
