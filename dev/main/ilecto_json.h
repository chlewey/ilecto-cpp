#ifndef __ILECTO_JSON_H__
#define __ILECTO_JSON_H__

#include "ilecto_str.h"
#include "ilecto_web.h"

namespace json {
using namespace il;

class json: public web::info {
	public:
	json(): web::info() {}
	json(web::info&I): web::info(I) {}
	~json() {}
	operator string&() { return this->toString(); }
	string& toString();
};

}
#endif
