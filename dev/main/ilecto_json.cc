#include "ilecto_json.h"

namespace json {
const string nullstr("");
string emptystr("");
	
string& json::toString() { return emptystr; }

}
