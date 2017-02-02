/*@ interlecto.h
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

class cfg_file: public web::info {
};

}

#endif
