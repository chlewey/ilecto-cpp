
#include "interlecto.h"

namespace html {
	const string nullstr("");
	const string opini("<");
	const string clini("</");
	const string nmend(">");
	const string sgend(">");
	tag empty_tag;
	
	string& tag::attrib_str() {
		string*sp = new string(nullstr);
		for(attrib_iterator it=attribs.begin(); it!=attribs.end(); ++it) {
			*sp += " ";
			*sp += it->first;
			*sp += "=\"";
			*sp += it->second;
			*sp += "\"";
		}
		return *sp;
	}

	string& tag::open_tag(bool nl,int level) {
		string*sp = new string(level<0?0:level,'\t');
		*sp += opini;
		*sp += tagname;
		*sp += attrib_str();
		*sp += nmend;
		if(nl) *sp+= "\n";
		return *sp;
	}

	string& tag::close_tag(bool nl,int level) {
		string*sp = new string(level<0?0:level,'\t');
		*sp += clini;
		*sp += tagname;
		*sp += nmend;
		if(nl) *sp+= "\n";
		return *sp;
	}

	string& tag::single_tag(bool nl,int level) {
		string*sp = new string(level<0?0:level,'\t');
		*sp += opini;
		*sp += tagname;
		*sp += attrib_str();
		*sp += sgend;
		if(nl) *sp+= "\n";
		return *sp;
	}
	
	string& block::inner_tags(int level) {
		string*sp = new string(nullstr);
		for(tag_iterator it=tags.begin(); it!=tags.end(); ++it) {
			*sp += (*it)->toString(level);
		}
		return *sp;
	}
	
	string& block::toString(int level) {
		string*sp = new string(nullstr);
		*sp += open_tag(true,level);
		*sp += inner_tags(level+1);
		if(sp->back() != '\n') sp->push_back('\n');
		*sp += close_tag(true,level);
		return *sp;
	}

	block& block::append(const string&Text,const string&TN,const string&id) {
		tags.push_back(new par(TN,Text,id));
		return *this;
	}

	string& par::toString(int level) {
		string*sp = new string(nullstr);
		*sp += open_tag(false,level);
		*sp += inner_tags();
		if(sp->back() == '\n') sp->pop_back();
		*sp += close_tag(true);
		return *sp;
	}

	string& span::toString(int level) {
		string*sp = new string(nullstr);
		*sp += open_tag(false,level);
		*sp += inner_tags(0);
		if(sp->back() == '\n') sp->pop_back();
		*sp += close_tag(false);
		return *sp;
	}

	string& html::toString(int level) {
		string*sp = new string("<!DOCTYPE html>\n");
		*sp += block::toString(-1);
		return *sp;
	}
}
