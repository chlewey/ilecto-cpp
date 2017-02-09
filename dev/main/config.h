/*@ config.h
 * 
 * This header defines the config::cfg_file class that allows to
 * read, write, and manipulate config files.
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "ilecto_str.h"
#include "ilecto_web.h"

namespace config {
typedef il::string string;

class cfg_file: public web::info {
	std::istream* _in;
	std::ostream* _out;
	bool changed, tcIn, tcOut;
	public:
	cfg_file(string&file_name);
	cfg_file(std::iostream&IOs): web::info(), _in(&IOs), _out(&IOs), changed(false), tcIn(false), tcOut(false) {}
	cfg_file(std::istream&inS, std::ostream&outS): web::info(), _in(&inS), _out(&outS), changed(false), tcIn(false), tcOut(false) {}
	cfg_file(cfg_file&CF): web::info(CF), _in(CF._in), _out(CF._out), changed(CF.changed), tcIn(false), tcOut(false) {} // copy
	~cfg_file() { if(changed) save(); if(tcIn) delete _in; if(tcOut) delete _out; }

	int load();
	virtual int save();
};

class cfg_reader: public cfg_file {
	public:
	cfg_reader(string&file_name);
	cfg_reader(std::istream&inS): cfg_file(inS,std::cerr) {}
	cfg_reader(cfg_reader&); // copy
	~cfg_reader();
	
	int save();
};

}//namespace

#endif
