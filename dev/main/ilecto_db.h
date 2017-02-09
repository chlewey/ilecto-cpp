/*@ ilecto_db.h
 * 
 * This header defines the il::db virtual class for handle a database
 * for the purposes of the Interlecto WS engine.
 * 
 * It offers also the csvdb::db class (implementation of il::db) which
 * implements a basic database based in CSV files.
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_DB_H__
#define __ILECTO_DB_H__

#include "ilecto_str.h"

namespace il {

typedef std::vector<string> vstring;

class db_index {
	public:
};

class db_result {
	public:
};

class db {
	public:
	virtual db_result& select(string&table, vstring&fields)=0;
};

}//namspace

namespace csvdb {

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
	db_result& select(string&table, vstring&fields);
};

}//namspace

#endif
