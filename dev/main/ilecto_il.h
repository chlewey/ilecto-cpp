#ifndef __ILECTO_IL_H__
#define __ILECTO_IL_H__

#include <string>
#include <string.h>
#include <map>
#include <vector>

namespace il {
class key;		// strings used for keys.
class string;	// string class with extra.
class info;     // keyed tree of information.
const size_t BSIZE=16;

class key {
	size_t _size, _res;
	char* data;
	void _set(size_t n,const char*src) { _size=n; _res=(1+_size/BSIZE)*BSIZE; data=new char[_res]; size_t i; for(i=0; i<n && src[i]; i++) data[i]=src[i]; data[i]=0; }
	void _del() { if(data) delete data; }
	public:
	key(): _size(0), _res(0), data(NULL) {}
	key(const char*str) { _set(strlen(str), str); }
	key(const char*str, size_t n) { _set(n, str); }
	key(const std::string S) { _set(S.size(), S.c_str()); }
	~key() { _del(); }
	
	key& operator=(const char*str) { _del(); _set(strlen(str), str); }
	key& operator=(const std::string S) { _del(); _set(S.size(), S.c_str()); }
	
	operator char*() { return data; }
};

class string: public std::string {
	public:
	string(const char*str): std::string(str) {}
};
extern string emptyStr;
extern const string nullStr;
extern const size_t npos;
typedef string request_t;

enum info_type {
	I_null, I_str, I_map, I_int, I_num, I_bool
};
class info_node {
	info_type _type;
	bool _new;
	union {
		string*Sp;
		info*Ip;
		long i;
		double f;
	};
	public:
	info_node(): _type(I_null), _new(false), i(0) {}
	info_node(const char*str): _type(I_str), _new(true), Sp(new string(str)) {}
	info_node(const string&S): _type(I_str), _new(true), Sp(new string(S)) {}
	info_node(info&I): _type(I_map), _new(false), Ip(&I) {}
	info_node(const info&I);
	info_node(long n): _type(I_int), _new(false), i(n) {}
	info_node(double n): _type(I_int), _new(false), f(n) {}
	info_node(bool b): _type(I_bool), _new(false), i(b) {}
	
	~info_node();
};

class str_vector: public std::vector<string> {
	public:
	str_vector(size_t n,const char*src[]);
	str_vector(const char**src);
};

class info_pair: public std::pair<key,info_node> {
	public:
	info_pair(const string&K,const info_node&N);
};

class info: public std::map<key,info_node> {
	public:
	info();
	info(const info&I);
	info(std::initializer_list<info_pair>L);
	~info();
};
extern info emptyInfo;

info_node::info_node(const info&I):
_type(I_map),
_new(true),
Ip(new info(I))
{
}

info_node::~info_node()
{
	if(_type==I_str) delete Sp;
	else if(_type==I_map && _new) delete Ip;
}


}//namespace

#endif
