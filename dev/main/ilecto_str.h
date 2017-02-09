/*@ ilecto_str.h
 * 
 * This header extends std::string class as il::string with some
 * common utilities
 * 
 *@ author:  Carlos E. Thompson P.
 *@ licence: copyleft, 2017
 * 
 */
#ifndef __ILECTO_STR_H__
#define __ILECTO_STR_H__

#ifndef NEWPTR
#define NEWPTR(CL,VAR) CL*VAR = new CL
#endif


#include <utility>
#include <string>
#include <sstream>
#include <vector>

namespace il {
extern const size_t npos;
extern const char* spaces;

enum entities {
	XML_ENCODE,
	XML_DECODE,
	HTML_ENCODE = 0,
	HTML_DECODE
};

class string;
typedef std::vector<string> string_vector;
typedef std::pair<string,string> string_pair;
typedef std::vector<string_pair> string_pair_vector;
extern const string nullstr;
extern string emptystr;
extern const string_pair_vector html_substs;

class string: public std::string {
	public:
	string(): std::string() {}
	string (const string& str): std::string(str) {}
	string (const string& str, size_t pos, size_t len = npos): std::string(str, pos, len) {}
	string (const char* s): std::string(s) {}
	string (const char* s, size_t n): std::string(s,n) {}
	string (size_t n, char c): std::string(n,c) {}
	template <class InputIterator>
	string  (InputIterator first, InputIterator last): std::string(first,last) {}
	string (std::initializer_list<char> inil): std::string(inil) {}
	//string (string&& str) noexcept: std::string(str) {}
	string (const std::string& str): std::string(str) {}
	string (const std::string& str, size_t pos, size_t len = npos): std::string(str, pos, len) {}
	//string (std::string&& str) noexcept: std::string(str) {}
	string (char c): std::string(1,c) {}
	~string() {}

	string& substitute(const string& what, const string& with=nullstr);
	string& substitute(const string_vector& what, const string& with=nullstr);
	string& substitute(const string_vector& what, const string_vector& with);
	string& substitute(const string_pair& subst) { return substitute(subst.first, subst.second); }
	string& substitute(const string_pair_vector& substs);

	string& ltrim(const char*s=spaces);
	string& ltrim(const char*s, size_t n);
	string& ltrim(const string& str) { return ltrim(str.c_str()); }
	string& ltrim(char c);
	string& rtrim(const char*s=spaces);
	string& rtrim(const char*s, size_t n);
	string& rtrim(const string& str) { return rtrim(str.c_str()); }
	string& rtrim(char c);
	string& trim(const char*s=spaces) { return ltrim(s).rtrim(s); }
	string& trim(const char*s, size_t n) { return ltrim(s,n).rtrim(s,n); }
	string& trim(const string& str) { return trim(str.c_str()); }
	string& trim(char c) { return ltrim(c).rtrim(c); }

	string& url_encode();
	string& url_decode();

	string& xml_escape();
	string& xml_unescape();
	string& html_escape();
	string& html_unescape();

	template<typename Out>
	void split(char c, Out result) const;
	string_vector split(char c='\n') const;
	string_pair split_first(char c='\n', size_t pos=0) const;
	string_pair split_last(char c='\n', size_t pos=npos) const;
};

inline string& ltrim(const string&str, const char* chars=spaces, size_t n=npos) { return (*new string(str)).ltrim(chars,n); }
inline string& rtrim(const string&str, const char* chars=spaces, size_t n=npos) { return (*new string(str)).rtrim(chars,n); }
inline string&  trim(const string&str, const char* chars=spaces, size_t n=npos) { return (*new string(str)). trim(chars,n); }

inline string& ltrim(const string&str, const string& chars) { return (*new string(str)).ltrim(chars); }
inline string& rtrim(const string&str, const string& chars) { return (*new string(str)).rtrim(chars); }
inline string&  trim(const string&str, const string& chars) { return (*new string(str)). trim(chars); }

inline string& ltrim(const string&str, char c) { return (*new string(str)).ltrim(c); }
inline string& rtrim(const string&str, char c) { return (*new string(str)).rtrim(c); }
inline string&  trim(const string&str, char c) { return (*new string(str)). trim(c); }

inline string_vector split(const string& str, char c='\n') { return str.split(c); }
inline string_vector split(const char* s, char c='\n') { return string(s).split(c); }

inline string& html_escape(const string& str) { return (*new string(str)).html_escape(); }
inline string& html_unescape(const string& str) { return (*new string(str)).html_unescape(); }
string& xml_escape(const string& str);
inline string& xml_unescape(const string& str) { return (*new string(str)).xml_unescape(); }

inline string& itohex(long int n, char fill='0', size_t len=0) {
	std::stringstream ss;
	ss << std::hex << n;
	NEWPTR(string,sp)(ss.str());
	if(len) {
		size_t l = sp->size();
		if(l<len)
			sp->replace(0,0,len-l,fill);
	}
	return *sp;
}

}
#endif
