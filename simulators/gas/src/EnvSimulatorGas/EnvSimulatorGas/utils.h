#pragma once

#include "pch.h"
#include <time.h>
#include "stringutils.h"

template <typename T> inline int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

inline string GetCurrentTimeStr() 
{
	time_t result = time(NULL);
	char strtime[26];
	ctime_s(strtime, sizeof strtime, &result);
	string stime = string(strtime);
	stime.pop_back();
	return stime;
}