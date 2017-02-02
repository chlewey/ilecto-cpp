/*@ interlecto.h
 * 
 * This header create classes that serve the web server environment
 * and a framework for sending content.
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_WEB_H__
#define __ILECTO_WEB_H__

#include "ilecto_str.h"
#include "ilecto_html.h"
#include <iostream>
#include <map>

namespace web {
using namespace il;

extern std::ostream&cout;
extern std::ostream&cerr;
extern std::istream&cin;

class info;
typedef std::map<string,info*> info_map;
typedef std::map<string,info*>::iterator info_iterator;
typedef std::map<string,info*>::const_iterator info_citerator;
typedef std::map<string,info*>::reverse_iterator info_reverse;
typedef std::map<string,info*>::const_reverse_iterator info_creverse;

class info {
	info_map*_data;
	string _value;

	public:
	void DEBUG(const string&msg="DEBUG info", int n=0) {
		cerr << string(n,'\t') << msg << "\n";
		if(_data==NULL)
			cerr << string(n,'\t') << "_data = NULL\n";
		else {
			cerr << string(n,'\t') << "_data = [\n";
			for(auto x: *_data) {
				x.second->DEBUG("DEBUG "+x.first,n+1);
			}
			cerr << string(n+1,'\t') << "]\n";
		}
		cerr << string(n,'\t') << "_value = \"" << _value << "\"\n\n";
	}

	public:
	info(): _data(new info_map), _value(nullstr) {}
	info(const info&I): _data(I._data), _value(I._value) {}
	info(const string&S): _data(NULL), _value(S) {}
	info(const string&key,info*Ip): _data(new info_map), _value(nullstr) { _data->emplace(key,Ip); }
	info(const string&key,info&I ): _data(new info_map), _value(nullstr) { _data->emplace(key,&I); }
	~info();

	info& operator=(const info&I) { if(_data!=NULL) delete _data; _data=I._data; _value=I._value; }
	info& operator=(const string&S) { if(_data!=NULL) delete _data; _value=S; }
	bool operator==(const info&) const;

	string& value() { return _value; }
	string& value(const string&keys);

	bool is_map() { return _data!=NULL; }
	bool is_string() { return !is_map(); }
	// map !!! NOTE: these functions will fail if NULL (i.e. string info)
	info_iterator  begin()       { return _data->begin(); }
	info_citerator begin() const { return _data->begin(); }
	info_iterator  end()       { return _data->end(); }
	info_citerator end() const { return _data->end(); }
	info_reverse  rbegin()       { return _data->rbegin(); }
	info_creverse rbegin() const { return _data->rbegin(); }
	info_reverse  rend()       { return _data->rend(); }
	info_creverse rend() const { return _data->rend(); }
	bool empty() const { return _data->empty(); }
	size_t size() const { return _data->size(); }
	size_t max_size() const { return _data->max_size(); }
	info*operator[](const string&key) { return (*_data)[key]; }
	info*at(const string&key) { return _data->at(key); }
	const info*at(const string&key) const { return _data->at(key); }
	info_iterator find(const string&key) { return _data->find(key); }
	size_t count(const string&key) { return _data->count(key); }
	bool key_exists(const string&key) const { return _data->count(key); }

	info* set(const string&key,info& I) { if(_data==NULL) _data = new info_map; return (*_data)[key] = &I; }
	info* set(const string&key,info*Ip) { if(_data==NULL) _data = new info_map; return (*_data)[key] = Ip; }
	info* set(const string&key,const string&value) {
		if(_data==NULL) _data = new info_map;
		info*x = new info(value);
		return (*_data)[key] = x;
	}

	virtual html::tag* html_struct() { return &html::empty_tag; }
};

extern info emptyinfo;

class enviro: public info {
	public:
	enviro(): info() {}
	enviro(int,char**,char**);
	enviro(const enviro&);
	~enviro();

	info& request();
	info& skin();

	string& server(const string&);
	string& get(const string&);
	string& post(const string&);
	string& cookie(const string&);
	string& request(const string&);
	string& session(const string&);

	string& header(const string&key,const string&val);
	string& headers() const;
	int status() const;
};

class content;
typedef html::tag htmlcode;
htmlcode* make_content(content&);

class content: public info {
	public:
	content(): info() {}
	content(enviro&);
	content(const content&);
	~content();
	html::tag* html_struct() { return make_content(*this); }
};

class format: public info {
	public:
	format(): info() {}
	format(enviro&);
	format(const format&);
	~format();

	format& set_title(const string&tit) { set("title", tit); }
	format& load(content&);

	string& xhtml();
	string& html();
	string& json();
	string& xml();
};

int main(enviro&);

/*
string& url_decode(const string&,size_t l=string::npos);
string& url_decode(string*);
string& url_encode(const string&);
/**/
}
#endif
