
#include "interlecto.h"
//#include <string.h>

int main(int argc, char **argv, char**envp) {
	web::enviro Enviro(argc, argv, envp);
	web::content Content(Enviro);
	web::format Page(Enviro);

	return web::main(Enviro, Page, Content);
}

namespace web {
	std::ostream&cout(std::cout);
	std::ostream&cerr(std::cerr);
	std::istream&cin(std::cin);

	const string nullstr("");
	string emptystr("");
	info emptyinfo;

	info::~info() {
	}
	
	string& info::value(const string&keys) {
		if(keys=="") return _value;
		string_pair kp = strbreak(keys, ':');
		info_iterator it=_data->find(kp.first);
		if(it==_data->end()) return emptystr;
		return it->second->value(kp.second);
	}

	enviro::enviro(int argc, char **argv, char**envp): info() {
		info*serverp = set("server", new info());
		string query(""), key(""), val("");
		size_t postN=0;
		for(size_t i=0; *(envp+i); ++i) {
			string s(*(envp+i));
		//	size_t n = s.find('=');
		//	if(n!=string::npos)
		//	key = s.substr(0,n);
		//	val = s.substr(n+1);
			string_pair sp = strbreak(s, '=');
			key = sp.first;
			val = sp.second;
			serverp->set(key, val);
			if(key=="QUERY_STRING") query=val;
			if(key=="CONTENT_LENGTH") postN=atol(val.c_str());
		}
		set("get_query", query);
		string_vector qv = split(query, '&');
		info*getp = new info;
		for(string&q: qv) {
			string_vector ql = split(q, '=');
			if(ql.size()<2) continue;
			getp->set(ql[0],url_decode(ql[1]));
		}
		set("get", getp);
		set("post_len", std::to_string(postN));

		if(postN>0) {
			char*data = new char[postN+1];
			cin.read(data,postN);
			data[postN] = '\0';
			set("post_query", data);
			string_vector pv = split(data, '&');
			info*postp = new info;
			for(string&p: pv) {
				string_vector pl = split(p, '=');
				if(pl.size()<2) continue;
				postp->set(pl[0],url_decode(pl[1]));
			}
			set("post", postp);
		}
	}

	enviro::~enviro() {
	}

	int enviro::status() const {
		return 0;
	}

	string& enviro::server(const string&key) {
		if(!key_exists("server")) return emptystr;
		if(!at("server")->key_exists(key)) return emptystr;
		return at("server")->at(key)->value();
	}
	
	string& enviro::get(const string&key) {
		if(!key_exists("get")) return emptystr;
		if(!at("get")->key_exists(key)) return emptystr;
		return at("get")->at(key)->value();
	}

	string& enviro::post(const string&key) {
		if(!key_exists("post")) return emptystr;
		if(!at("post")->key_exists(key)) return emptystr;
		return at("post")->at(key)->value();
	}

	string& enviro::cookie(const string&key) {
		if(!key_exists("cookie")) return emptystr;
		if(!at("cookie")->key_exists(key)) return emptystr;
		return at("cookie")->at(key)->value();
	}

	string& enviro::session(const string&key) {
		if(!key_exists("session")) return emptystr;
		if(!at("session")->key_exists(key)) return emptystr;
		return at("session")->at(key)->value();
	}

	string& enviro::request(const string&key) {
		string&rq(emptystr);
		if((rq=cookie(key))!=emptystr) return rq;
		if((rq=post(key))!=emptystr) return rq;
		if((rq=get(key))!=emptystr) return rq;
		return emptystr;
	}

	string& enviro::headers() const {
		string*sp = new string("Content-type: text/html;charset=utf-8\r\n\r\n");
		return *sp;
	}

	info& enviro::request() {
		return *new info();
	}

	info& enviro::skin() {
		return *new info();
	}

	format::format(enviro&E): info("enviro",E) {
	}

	format::~format() {
	}
	
	format& format::load(content& C) {
		set("content", C);
		return *this;
	}

	string& format::html() {
		html::html Html;
		if(key_exists("title"))
			Html.set_title((*this)["title"]->value());
		if(key_exists("content"))
			Html.body()->append( at("content")->html_struct() );
		return Html.toString();
	}

	content::content(enviro&E): info("enviro",E) {
	}

	content::~content() {
	}
	
	string& url_decode(const string&S,size_t l) {
		size_t n = S.size();
		const char*orig = S.c_str();
		const char*last = l!=string::npos? orig+l: orig+n;
		char*dest = new char[n+2];
		unencode(orig,last,dest);
		return *new string(dest);
	}
	string& url_encode(const string&S) { return *new string(S); }

}
