#ifndef __ILECTO_HTML_H__
#define __ILECTO_HTML_H__

#include <iostream>
#include <vector>
#include <string>
#include <map>
//#include <stdio.h>
//#include <stdlib.h>

//#include <cgicc/CgiDefs.h>
//#include <cgicc/Cgicc.h>
//#include <cgicc/HTTPHTMLHeader.h>
//#include <cgicc/HTMLClasses.h>

namespace html {

typedef std::string string;
typedef std::map<string,string> attrib_map;
typedef std::map<string,string>::iterator attrib_iterator;
typedef std::pair<string,string> attrib_pair;
extern const string nullstr, opini, clini, nmend, sgend;

class tag {
	string tagname;
	attrib_map attribs;
	public:
	tag(const string&name=nullstr,const string&id=nullstr): tagname(name) {
		if(id!=nullstr) attribs["id"] = id;
	}
	virtual ~tag() {}
	string& operator[](const string&key) { return attribs[key]; }
	const string&  name() const { return tagname; }
	string& set_at(const string&key,const string&value) { return attribs[key]=value; }
	string& get_at(const string&key) { return attribs[key]; }
	
	virtual bool empty() const { return true; }
	virtual tag& append(tag*Tp) { return *this; }
	
	operator string&() { return this->toString(); }
	virtual string& toString(int level=0) { return *new string; }
	string& attrib_str();
	string& open_tag(bool nl=false,int level=0);// { return opini + tagname + attrib_str() + nmend; }
	string& close_tag(bool nl=false,int level=0);// { return clini + tagname + nmend; }
	string& single_tag(bool nl=false,int level=0);// { return opini + tagname + attrib_str() + sgend; }
};

extern tag empty_tag;

class text: public tag {
	string _text;
	public:
	text(const string&src): tag(nullstr), _text(src) {}
	~text() {}
	bool empty() { return _text.size()==0; }

	text& operator=(const string&src) { _text = src; }
	string& toString(int level=0) { string*sp=new string(level,'\t'); *sp += _text; return *sp; }
};

class simple: public tag {
	public:
	simple(const string&name,const string&id=nullstr): tag(name,id) {}
	~simple() {}
	bool empty() const { return true; }
	string& toString(int level=0) { return single_tag(false,level); }
};

class sblock: public simple {
	public:
	sblock(const string&name,const string&id=nullstr): simple(name,id) {}
	~sblock() {}
	bool empty() const { return true; }
	string& toString(int level=0) { return single_tag(true,level); }
};

typedef std::vector<tag*> tag_list;
typedef std::vector<tag*>::iterator tag_iterator;
typedef std::vector<tag*>::reverse_iterator tag_reverse;

class block: public tag {
	tag_list tags;
	public:
	block(const string&name,const string&id=nullstr): tag(name,id) {}
	~block() { tags.clear(); }
	
	block& append(tag&T)  { tags.push_back(&T); return *this; }
	block& append(tag*Tp) { tags.push_back(Tp); return *this; }
	block& append(const string&Text,const string&TN="p",const string&id=nullstr);
	
	tag_iterator begin() { return tags.begin(); };
	tag_iterator end() { return tags.end(); };
	tag_reverse rbegin() { return tags.rbegin(); };
	tag_reverse rend() { return tags.rend(); };
	size_t size() const { return tags.size(); }
	size_t max_size() const { return tags.max_size(); }
	void resize(size_t n, tag*Tp=NULL ) { tags.resize(n, Tp); }
	size_t capacity() const { return tags.capacity(); }
	bool empty() const { return tags.empty(); }
	void reserve(size_t n) { tags.reserve(n); }
	      tag* operator[] (size_t n)       { return tags[n]; }
	const tag* operator[] (size_t n) const { return tags[n]; }
	      tag* at(size_t n)       { return tags.at(n); }
	const tag* at(size_t n) const { return tags.at(n); }
	      tag* front()       { return tags.front(); }
	const tag* front() const { return tags.front(); }
	      tag* back()       { return tags.back(); }
	const tag* back() const { return tags.back(); }

	virtual string& toString(int level=0);
	string& inner_tags(int level=0);
};

class par: public block {
	public:
	par(const string&name,const string&value=nullstr,const string&id=nullstr): block(name,id) { if(value!=nullstr) append(new text(value)); }
	~par() {}
	string& toString(int level=0);
};

class span: public par {
	public:
	span(const string&name,const string&value=nullstr,const string&id=nullstr): par(name,value,id) {}
	~span() {}
	string& toString(int level=0);
};

class html: public block {
	string _title;
	public:
	html(const string&id=nullstr): block("html",id), _title(nullstr) {
		this->append(new block("head"));
		this->append(new block("body"));
	}
	~html() {}
	      tag* head()       { return this->at(0); }
	const tag* head() const { return this->at(0); }
	      tag* body()       { return this->at(1); }
	const tag* body() const { return this->at(1); }
	string& toString(int level=0);

	html& set_title(string& tit) {
		_title = tit;
		par*Tp=new par("title");
		Tp->append(new text(tit));
		head()->append(Tp);
		return *this;
	}
};

// specific classes
class meta: public sblock {
	public:
	meta(const string&name,const string&cont): sblock("meta") { set_at("name",name); set_at("content",cont); }
};

class metachar: public sblock {
	public:
	metachar(const string&charset="UTF-8"): sblock("meta") { set_at("charset",charset); }
};

class link: public sblock {
	public:
	link(const string&rel,const string&href): sblock("link") { set_at("rel",rel); set_at("href",href); }
};

class link_css: public link {
	public:
	link_css(const string&href): link("stylesheet",href) { set_at("type","text/css"); }
};

class link_scr: public par {
	public:
	link_scr(const string&href): par("script") { set_at("href",href); }
};

class script: public block {
	public:
	script(const string&scr): block("script") { append(new text(scr)); }
};

class form: public block {
	public:
	form(const string&method,const string&action=nullstr,const string&id=nullstr): block("form",id) { set_at("method",method); if(action!=nullstr) set_at("action",action); }
};

class label: public span {
	public:
	label(const string&For,const string&value=nullstr,const string&id=nullstr): span("label",value,id) { set_at("for",For); }
};

class input: public simple {
	public:
	input(const string&id,const string&name=nullstr,const string&value=nullstr): simple("input",id) { set_at("name",name==nullstr?id:name); if(value!=nullstr) set_at("value",value); }
};

class submit: public simple {
	public:
	submit(const string&value=nullstr,const string&id=nullstr): simple("input",id) { set_at("type","submit"); if(value!=nullstr) set_at("value",value); }
};

}
#endif
