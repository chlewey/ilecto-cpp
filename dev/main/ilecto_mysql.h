/*@ ilecto_mysql.h
 * 
 * This header defines the xml::xml class
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_MYSQL_H__
#define __ILECTO_MYSQL_H__

#include "ilecto_db.h"

namespace mysql {

typedef il::string string;
typedef il::vstring vstring;

class db_index: public il::db_index {
	public:
};

class db_result: public il::db_result {
	public:
};

class db: public il::db {
	public:
	db(const string&location,const string&user,const string&passwd,const string&database="",const string&prefix="");
	~db();
	
	string& escape(const string&str);
	
	db_result& select(string&table, vstring&fields);
};

}//namspace
#endif

