/*@ interlecto.h
 * 
 * This header calls the necesary environment for the Interlecto WS
 * Engine and the Interlecto WS modules.
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __INTERLECTO_H__
#define __INTERLECTO_H__

#define NEWPTR(CL,VAR) CL*VAR = new CL

#include "ilecto_str.h"
#include "ilecto_html.h"
#include "ilecto_xml.h"
#include "ilecto_json.h"
#include "ilecto_web.h"
#include "config.h"

#endif
