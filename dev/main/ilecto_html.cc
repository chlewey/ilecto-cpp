
#include "interlecto.h"

namespace html {

const string opini("<");
const string clini("</");
const string nmend(">");
const string sgend("/>");
tag empty_tag;

string&r_entities(string&src) {
	size_t pos=src.find('&');
	while( pos!=npos ) {
		src.replace(pos,1,"&amp;");
		pos=src.find('&',pos+1);
	}
	return src;
}

string& tag::attrib_str(bool as_xml) {
	string*sp = new string(nullstr);
	for(auto x: attribs) {
		string key(x.first), val(x.second);
		if(as_xml)
			val.xml_escape();
		else
			val.html_escape();
		*sp += " ";
		*sp += key;
		if(as_xml || npos != val.find_first_of(" \\/&:")) {
			*sp += "=\"";
			*sp += val;
			*sp += "\"";
		} else {
			*sp += "=";
			*sp += val;
		}
	}
	return *sp;
}

string& tag::open_tag(bool nl,int level,bool as_xml) {
	string*sp = new string(level<0?0:level,'\t');
	*sp += opini;
	*sp += tagname;
	*sp += attrib_str(as_xml);
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

string& tag::single_tag(bool nl,int level,bool as_xml) {
	string*sp = new string(level<0?0:level,'\t');
	*sp += opini;
	*sp += tagname;
	*sp += attrib_str(as_xml);
	*sp += as_xml? sgend: nmend;
	if(nl) *sp+= "\n";
	return *sp;
}

string& text::toString(int level,bool as_xml) {
	string*sp=as_xml? &xml_escape(_text): &html_escape(_text);
	sp->replace(0,0,level,'\t');
	return *sp;
}

string& block::inner_tags(int level,bool as_xml) {
	string*sp = new string(nullstr);
	for(auto x: tags) {
		*sp += x->toString(level,as_xml);
	}
	return *sp;
}

string& block::toString(int level,bool as_xml) {
	string*sp = new string(nullstr);
	if(as_xml && empty()) {
		*sp += single_tag(true,level,as_xml);
	} else {
		*sp += open_tag(true,level,as_xml);
		*sp += inner_tags(level+1,as_xml);
		if(sp->back() != '\n') sp->push_back('\n');
		*sp += close_tag(true,level);
	}
	return *sp;
}

block& block::append(const string&Text,const string&TN,const string&id) {
	tags.push_back(new par(TN,Text,id));
	return *this;
}

string& par::toString(int level,bool as_xml) {
	string*sp = new string(nullstr);
	if(as_xml && empty()) {
		*sp += single_tag(true,level,as_xml);
	} else {
		*sp += open_tag(false,level,as_xml);
		*sp += inner_tags(0,as_xml);
		if(sp->back() == '\n') sp->pop_back();
		*sp += close_tag(true);
	}
	return *sp;
}

string& span::toString(int level,bool as_xml) {
	string*sp = new string(nullstr);
	if(as_xml && empty()) {
		*sp += single_tag(false,level,as_xml);
	} else {
		*sp += open_tag(false,level,as_xml);
		*sp += inner_tags(0,as_xml);
		if(sp->back() == '\n') sp->pop_back();
		*sp += close_tag(false);
	}
	return *sp;
}

string& html::toString(int level,bool as_xml) {
	string*sp = new string("<!DOCTYPE html>\n");
	*sp += block::toString(level,as_xml);
	return *sp;
}

}// namespace
