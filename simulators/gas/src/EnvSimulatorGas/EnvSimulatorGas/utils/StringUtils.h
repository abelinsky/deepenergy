#pragma once
#include "pch.h"
#include <boost/format.hpp>
#include <sstream>
#include <iomanip>

//inline std::string string_format(const std::string fmt, ...)
//{
//	DoLog("string_format started");
//	int size = ((int)fmt.size()) * 2 + 50;   // Use a rubric appropriate for your code
//	std::string str;
//	va_list ap;
//	while (1) {     // Maximum two passes on a POSIX system...
//		str.resize(size);
//		va_start(ap, fmt);
//		int n = vsnprintf((char *)str.data(), size, fmt.c_str(), ap);
//		va_end(ap);
//		if (n > -1 && n < size) {  // Everything worked
//			str.resize(n);
//			return str;
//		}
//		if (n > -1)  // Needed size returned
//			size = n + 1;   // For null char
//		else
//			size *= 2;      // Guess at a larger size (OS specific)
//	}
//
//	DoLog("string_format ended");
//
//	return str;
//}

inline bool string_replace(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}

inline bool eol(istream &in) // end of line 
{
	char c;
	c = in.rdbuf()->sgetc();
	return (c == '\n');
}

inline string itos(int i)
{
	//return string_format("%d", i);
	return (boost::format("%d") % i).str();
}

inline string ftos(double d, int i = -1)
{
	i = (i == -1) ? 2 : i;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << d;
	return stream.str();
}

inline int stoi(const string& s)
{
	return atoi(s.c_str());
}

inline string operator << (string& s, double d)
{
	//s = string_format("%.2f", d);
	//return s;
	s = (boost::format("%.2f") % d).str();
	return s;
}

inline string operator << (string& s, int i)
{
	//s = string_format("%d", i);
	//return s;
	s = (boost::format("%d") % i).str();
	return s;
}
