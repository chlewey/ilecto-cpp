/*@ interlecto.h
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

class db {
};

}//namspace

namespace csvdb {

class db: public il::db {
};

}//namspace

#endif
