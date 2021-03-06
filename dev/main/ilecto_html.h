/*@ ilecto_html.h
 * 
 * This header creates an html::html class and different html::tag
 * classes
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_HTML_H__
#define __ILECTO_HTML_H__

#include "ilecto_str.h"
#include <iostream>
#include <map>

namespace html {
using namespace il;

typedef std::map<string,string> attrib_map;
typedef std::map<string,string>::iterator attrib_iterator;
typedef std::pair<string,string> attrib_pair;
extern const string opini, clini, nmend, sgend;

string&r_entities(string&src);
inline string&entities(const string&src) { string*sp=new string(src); return r_entities(*sp); }

class tag {
	string tagname;
	attrib_map attribs;
	public:
	tag(const string&name=nullstr,const string&id=nullstr): tagname(name) {
		if(id!=nullstr) attribs["id"] = id;
	}
	tag(const tag&T): tagname(T.tagname), attribs(T.attribs) {}
	virtual ~tag() {}
	string& operator[](const string&key) { return attribs[key]; }
	const string&  name() const { return tagname; }
	string& set_at(const string&key,const string&value) { return attribs[key]=value; }
	string& get_at(const string&key) { return attribs[key]; }

	virtual bool empty() const { return true; }
	virtual tag& append(tag*Tp) { return *this; }

	operator string&() { return this->toString(); }
	virtual string& toString(int level=0,bool as_xml=false) { return *new string; }
	string& attrib_str(bool as_xml=false);
	string& open_tag(bool nl=false,int level=0,bool as_xml=false);// { return opini + tagname + attrib_str() + nmend; }
	string& close_tag(bool nl=false,int level=0);// { return clini + tagname + nmend; }
	string& single_tag(bool nl=false,int level=0,bool as_xml=false);// { return opini + tagname + attrib_str() + sgend; }
};

extern tag empty_tag;

class text: public tag {
	string _text;
	public:
	text(const string&src): tag(nullstr), _text(src) {}
	~text() {}
	bool empty() { return _text.size()==0; }

	text& operator=(const string&src) { _text = src; }
	string& toString(int level=0,bool as_xml=false);
};

class simple: public tag {
	public:
	simple(const string&name,const string&id=nullstr): tag(name,id) {}
	~simple() {}
	bool empty() const { return true; }
	string& toString(int level=0,bool as_xml=false) { return single_tag(false,level,as_xml); }
};

class sblock: public simple {
	public:
	sblock(const string&name,const string&id=nullstr): simple(name,id) {}
	~sblock() {}
	bool empty() const { return true; }
	string& toString(int level=0,bool as_xml=false) { return single_tag(true,level,as_xml); }
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

	virtual string& toString(int level=0,bool as_xml=false);
	string& inner_tags(int level=0,bool as_xml=false);
};

class par: public block {
	public:
	par(const string&name,const string&value=nullstr,const string&id=nullstr): block(name,id) { if(value!=nullstr) append(new text(value)); }
	~par() {}
	string& toString(int level=0,bool as_xml=false);
};

class span: public par {
	public:
	span(const string&name,const string&value=nullstr,const string&id=nullstr): par(name,value,id) {}
	~span() {}
	string& toString(int level=0,bool as_xml=false);
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
	string& toString(int level=-1,bool as_xml=false);

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

class caption: public par {
	public:
	caption(const string&Caption=nullstr,const string&id=nullstr): par("caption",Caption,id) {}
};

class table: public block {
	public:
	table(const string&id=nullstr,const string&Caption=nullstr): block("table",id) { if(Caption!=nullstr) append(new caption(Caption)); }
};

class tr_comp: public par {
	public:
	tr_comp(const string&id=nullstr): par("tr",nullstr,id) {}
};

class td_comp: public span {
	public:
	td_comp(const string&Text=nullstr,const string&id=nullstr): span("td",Text,id) {}
};

class th_comp: public span {
	public:
	th_comp(const string&Text=nullstr,const string&id=nullstr): span("th",Text,id) {}
};

class tr: public block {
	public:
	tr(const string&id=nullstr): block("tr",id) {}
};

class td: public par {
	public:
	td(const string&Text=nullstr,const string&id=nullstr): par("td",Text,id) {}
};

class th: public par {
	public:
	th(const string&Text=nullstr,const string&id=nullstr): par("th",Text,id) {}
};

}
#endif
