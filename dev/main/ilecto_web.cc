
#include "interlecto.h"

int main(int argc, char **argv, char**envp) {
	web::enviro Enviro(argc, argv, envp);
	web::content Content(Enviro);
	web::format Page(Enviro);

	return web::main(Enviro);
}

namespace web {
	//using namespace il;
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
		auto kp = keys.split_first(':');
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
			auto sp = s.split_first('=');
			key = sp.first;
			val = sp.second;
			serverp->set(key, val);
			if(key=="QUERY_STRING") query=val;
			if(key=="CONTENT_LENGTH") postN=atol(val.c_str());
		}
		set("get_query", query);
		auto qv = query.split('&');
		info*getp = new info;
		for(string&q: qv) {
			auto ql = q.split_first('=');
			getp->set(ql.first,ql.second.url_decode());
		}
		set("get", getp);
		set("post_len", std::to_string(postN));

		if(postN>0) {
			char*data = new char[postN+1];
			cin.read(data,postN);
			data[postN] = '\0';
			set("post_query", data);
			auto pv = split(data,'&');
			info*postp = new info;
			for(string&p: pv) {
				auto pl = p.split_first('=');
				postp->set(pl.first,pl.second.url_decode());
			}
			set("post", postp);
		}
		
		string req = value("server:REQUEST_URI");
		if(req==nullstr) req = value("server:REDIRECT_URL");
		req.url_decode();
		set("request",req);
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

	string& enviro::header(const string&key,const string&val) {
		if(!key_exists("headers"))
			set("headers",new info);
		at("headers")->set(key,val);
	}

	string& enviro::headers() const {
		NEWPTR(string,sp);
		if(key_exists("headers"))
			for(auto x: *at("headers"))
				*sp += x.first + ": " + x.second->value() + "\r\n";
		else
			*sp += "Content-type: text/html;charset=utf-8\r\n";
		*sp += "\r\n";
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
		C.set("page", this);
		return *this;
	}

	string& format::html() {
		NEWPTR(html::html,Hp);
		if(key_exists("title"))
			Hp->set_title((*this)["title"]->value());
		if(key_exists("content"))
			Hp->body()->append( at("content")->html_struct() );
		return Hp->toString();
	}

	string& format::xhtml() {
		NEWPTR(html::html,Hp);
		if(key_exists("title"))
			Hp->set_title((*this)["title"]->value());
		if(key_exists("content"))
			Hp->body()->append( at("content")->html_struct() );
		Hp->set_at("xmlns", "http://www.w3.org/1999/xhtml");
		return Hp->toString(0,true);
	}

	string& format::xml() {
		NEWPTR(xml::xml,Xp);
		return Xp->toString();
	}

	string& format::json() {
		NEWPTR(json::json,Jp);
		return Jp->toString();
	}

	content::content(enviro&E): info("enviro",E) {
	}

	content::~content() {
	}
	
	/*
	string& url_decode(string*Sp) {
		size_t n = Sp->size();
		const char*orig = Sp->c_str();
		char*dest = new char[n+2];
		unencode(dest,orig,n+1);
		Sp->replace(Sp->begin(),Sp->end(),dest);
		delete dest;
		return *Sp;
	}
	string& url_decode(const string&S,size_t l) {
		size_t n = S.size();
		const char*orig = S.c_str();
		const char*last = l!=string::npos? orig+l: orig+n;
		char*dest = new char[n+2];
		unencode(dest,orig,l==NPOS?n:l);
		string*ans = new string(dest);
		delete dest;
		return *ans;
	}
	string& url_encode(const string&S) { return *new string(S); }
	/**/
}
