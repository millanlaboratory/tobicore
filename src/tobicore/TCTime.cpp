/*
	Copyright (C) 2011 Francesco Leotta <francescoleotta@hotmail.com>
	Copyright (C) 2009-2011  EPFL (Ecole Polytechnique Fédérale de Lausanne)
	Michele Tavella <michele.tavella@epfl.ch>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "TCTime.hpp"

#ifdef WIN32
#include <windows.h>
#include <time.h>
#else
#include <sys/time.h>
#endif

#if defined WIN32 || defined __MINGW32__ 
int gettimeofday (struct timeval *tv, struct timezone *tz) {
	FILETIME ft;
	unsigned __int64 tmpres = 0;
	static int tzflag;
 
	if (NULL != tv) {
		GetSystemTimeAsFileTime(&ft);

		tmpres |= ft.dwHighDateTime;
		tmpres <<= 32;
		tmpres |= ft.dwLowDateTime;
 
		// converting file time to unix epoch
		tmpres -= 11644473600000000ULL; 
		tmpres /= 10;  // convert into microseconds
		tv->tv_sec = (long)(tmpres / 1000000UL);
		tv->tv_usec = (long)(tmpres % 1000000UL);
	}
 
	if (NULL != tz) {
		if (!tzflag) {
			_tzset();
			tzflag++;
		}
		tz->tz_minuteswest = _timezone / 60;
		tz->tz_dsttime = _daylight;
	}
 
	return 0;
}
#endif

/*
void timerclear(struct timeval *tvp) {
	ZeroMemory(tvp, sizeof(timeval));
}

int timerisset(struct timeval *tvp) {
	if (tvp->tv_sec || tvp->tv_usec)
		return 1;
	else
		return 0;
}
*/

void TCSleep(double ms) {
	timeval tm;
	tm.tv_sec = 0;
	tm.tv_usec = 1000*(long)ms;
#ifdef WIN32
	Sleep((DWORD)ms);
#else
	select(0, 0, 0, 0, &tm);
#endif
}
