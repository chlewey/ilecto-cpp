
#include "ilecto_il.h"
//#include<string>
//#include<vector>
#include<iostream>
//#include<map>

using namespace il;
/*
class string;
class str_vector;
typedef std::map<string,string> str_map;
typedef std::pair<string,string> str_pair;
const size_t npos=std::string::npos;

class string: public std::string {
	public:
	string(const char*str): std::string(str) {}
	string(const std::string&S): std::string(S) {}

	str_pair& cut(char c, size_t n=0) const;
	str_pair& cut(const string&S, size_t n=0) const;
	str_pair& rcut(char c, size_t n=npos) const;
	str_pair& rcut(const string&S, size_t n=npos) const;
	str_vector& split(char c) const;
	str_vector& split(const string&S) const;
	string& join(const str_vector&) const;
	string& join(const str_pair&) const;
};

typedef string request_t;
typedef std::vector<string>::iterator       svec_itor;
typedef std::vector<string>::const_iterator svec_itor_c;
string emptyStr="";
const string nullStr="";

class str_vector: public std::vector<string> {
	public:
	str_vector(size_t n, const char*v[]);
	str_vector(const char**nv);
	string& join(const string&S="") const { return S.join(*this); }
};

class info;
class info_map;
enum info_type {
	I_null,
	I_map,
	I_str,
	I_mix
};
class info_pair: public std::pair<string,info*>{
	public:
	info_pair(const string&K,const string&V);
	info_pair(const string&K,const info_map&M);
	info_pair(const string&K,const info&I);
};
class info_map: public std::map<string,info*> {
	public:
	info_map() {}
	info_map(const str_map&SM);
	info_map(const info_map&M): std::map<string,info*>(M) {}
	info_map(std::initializer_list<info_pair>L);

	bool insert(const string&K, const string&V)   { auto r = std::map<string,info*>::insert(info_pair(K,V)); return r.second; }
	bool insert(const string&K, const info_map&M) { auto r = std::map<string,info*>::insert(info_pair(K,M)); return r.second; }
	bool insert(const string&K, const info&I)     { auto r = std::map<string,info*>::insert(info_pair(K,I)); return r.second; }
};
info_map emptyInfo;
class info {
	info_type _type;
	string   *Sp;
	info_map *Mp;
	public:
	info(): _type(I_null), Sp(NULL), Mp(NULL) {}
	info(const char*str): _type(I_str), Mp(NULL) { Sp=new string(str); }
	info(const string&S): _type(I_str), Mp(NULL) { Sp=new string(S);   }
	info(const str_map&SM): _type(I_map), Sp(NULL), Mp(new info_map(SM)) {}
	info(const info_map&M): _type(I_map), Sp(NULL), Mp(new info_map(M))  {}
	info(std::initializer_list<info_pair>L): _type(I_map), Sp(NULL), Mp(new info_map(L))  {}
	~info() { if(Sp!=NULL) delete Sp; if(Mp!=NULL) delete Mp; }
	
	bool insert(const string&K, const string&V)   { return Mp->insert(K,V); }
	bool insert(const string&K, const info_map&M) { return Mp->insert(K,M); }
	bool insert(const string&K, const info&I)     { return Mp->insert(K,I); }
	
	string& get(const string&key);
	string& set(const string&key, const string&V);
};

info_pair::info_pair(const string&K,const string&V):   std::pair<string,info*>(K,new info(V)) {}
info_pair::info_pair(const string&K,const info_map&M): std::pair<string,info*>(K,new info(M)) {}
info_pair::info_pair(const string&K,const info&I):     std::pair<string,info*>(K,new info(I)) {}
*/

class server: public info {
	public:
	server(str_vector&);
	request_t& request();
};

class site: public info {
	public:
	site(server&,const str_vector&);
};

class page: public info {
	public:
	page(request_t&,site&);
	void build();
	string& headers();
	string& contents();
};

int main(int argc,const char*argv[],const char**env) {
	str_vector args(argc,argv), enviro(env);
	server Server(enviro);

	site Site(Server, args);
	page Page(Server.request(), Site);
	Page.build();
	std::cout << Page.headers();
	std::cout << Page.contents();
	return 0;
}

str_vector::str_vector(size_t n, const char*v[]) {
	for(size_t i=0; i<n; i++)
		emplace_back(v[i]);
}

str_vector::str_vector(const char**nv) {
	for(const char**p=nv; *p!=NULL; p++)
		emplace_back(*p);
}

/*
info_map::info_map(std::initializer_list<info_pair>L) {
	for(auto x: L)
		emplace( x );
}
*/

server::server(str_vector&env) {
	// load server and request environmental variables, translate them and build a data structure
}

site::site(server&serv,const str_vector&args) {
	// load server configuration from binary config file, text config file, and database (if applies).
}

request_t& server::request() {
	// return the request part of the environment
}

page::page(request_t&request, site&Site):
info({
	{"request",request},
	{"site",Site},
	{"headers",emptyInfo},
	{"response",emptyStr},
	})
{

}

void page::build() {
	// 
}

string& page::headers() {
	// 
	return *new string("Content-type: text/plain;charset=utf-8\r\n\n");
}

string& page::contents() {
	// 
	return *new string("Hello, World!\n");
}

