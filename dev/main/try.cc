
#include "ilecto_il.h"
#include<iostream>

using namespace il;

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

