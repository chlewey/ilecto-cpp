/*@ interlecto.h
 * 
 * This header defines the xml::xml class
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_XML_H__
#define __ILECTO_XML_H__

#include "ilecto_html.h"
#include "ilecto_web.h"

namespace xml {
using namespace il;

class tag:public html::tag {
	html::tag*_tag;
	public:
	tag(): _tag(new html::tag) {}
	tag(const tag&T): _tag(T._tag) {}
	string&toString(int level=0);
};

class text:public html::text {
	public:
	string&toString(int level=0);
};

class xml:public web::info {
	tag*root;
	public:

	operator string&() { return this->toString(); }
	string& toString() { return root->toString(); }
};

}
#endif
