#include "ilecto_str.h"
#include <iostream>

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
	return *this;
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
	for(size_t pos = find('%'); pos != npos; pos = find('%',pos)) {
		replace(pos,3,string(hex2char(substr(pos+1))));
	}
}

char* xml_valid_chars() {
	static char* ans(NULL);
	if(ans==NULL) {
		ans = new char[128];
		char*p = ans;
		for(char i='\t'; i<='\n'; i++)
			*p++ = i;
		for(char i=' '; i<'&'; i++)
			*p++ = i;
		for(char i='&'+1; i<'<'; i++)
			*p++ = i;
		*p++ = '=';
		for(char i='>'+1; i<127; i++)
			*p++ = i;
		*p = 0;
	}
	return ans;
}
void xml_append_escape(string&dest, const string&src, size_t*pt) {
	if(*pt==npos) return;
	unsigned char c=src[*pt];
	if((int)(0xe0&c) == (int)0xc0) {
		unsigned char c2=src[1+*pt];
		long n = ((0x1f&(long)c)<<6) + (0x3f&(long)c2);
		std::cerr << n << '\n';
		dest += "&#x";
		dest += itohex( n );
		dest += ";";
		*pt += 2;
	} else if(0xf0&c == 0xe0) {
		unsigned char c2=src[1+*pt];
		unsigned char c3=src[2+*pt];
		long n = ((0x0f&(long)c)<<12) + ((0x3f&(long)c2)<<6) + (0x3f&(long)c3);
		dest += "&#x";
		dest += itohex( n );
		dest += ";";
		*pt += 3;
	} else if(0xf8&c == 0xf0) {
		unsigned char c2=src[1+*pt];
		unsigned char c3=src[2+*pt];
		unsigned char c4=src[3+*pt];
		long n = ((0x0f&(long)c)<<18) + ((0x3f&(long)c2)<<12) + ((0x3f&(long)c3)<<6) + (0x3f&(long)c4);
		dest += "&#x";
		dest += itohex( n );
		dest += ";";
		*pt += 4;
	} else if(0xfc&c == 0xf8) {
		unsigned char c2=src[1+*pt];
		unsigned char c3=src[2+*pt];
		unsigned char c4=src[3+*pt];
		unsigned char c5=src[4+*pt];
		long n = ((0x0f&(long)c)<<24) + ((0x3f&(long)c2)<<18) + ((0x3f&(long)c3)<<12) + ((0x3f&(long)c4)<<6) + (0x3f&(long)c5);
		dest += "&#x";
		dest += itohex( n );
		dest += ";";
		*pt += 5;
	} else {
		dest += "&#x";
		dest += itohex( c );
		dest += ";";
		*pt += 1;
	}
}

string& xml_escape(const string&src) {
	NEWPTR(string,sp);
	const char* valid=xml_valid_chars();
	for(size_t pos=0; pos!=npos; ) {
		size_t d = src.find_first_not_of(valid,pos);
		if(npos==d) {
			*sp += src.substr(pos);
			break;
		}
		*sp += src.substr(pos,d-pos);
		pos = d;
		xml_append_escape(*sp,src,&pos);
	}
	return *sp;
}

string& string::xml_escape() {
	return *this = il::xml_escape(*this);
}

string& string::xml_unescape() {
	return *this;
}

const string_pair_vector html_substs = {
	{"&", "&amp;"},
	{"<", "&lt;"},
	{">", "&gt;"},
};

string& string::html_escape() {
	return substitute(html_substs);
}

string& string::html_unescape() {
	return *this;
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

string& string::substitute(const string& what, const string& with) {
	size_t len = what.size(), sub=with.rfind(what), d;
	d = sub==npos? 0: sub+1;
	for(size_t pos = find(what); pos != npos; pos = find(what,pos+d))
		replace(pos, len, with);
	return *this;
}

string& string::substitute(const string_pair_vector& substs) {
	for(auto subst: substs)
		substitute(subst);
	return *this;
}


}//namespace
