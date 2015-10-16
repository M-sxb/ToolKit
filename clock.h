// this file is under no license.
/** @file Clock.h
	@brief Clock.h contains class of Clock and any others that have the same means.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015<\b> 

	- builded this file.
	- add class UnitOfTime, class Clock_Traits, class DefaultClock.
	- now only support \p char as char traits, when return the unit of time.
*/


#ifndef Clock_Head
#define Clock_Head


#include "config.h"
#include <ctime>

#include "UnitOfSelecter.h" // for UnitOfSelecter


//! @todo ? better abstract class: UnitOf.
struct UnitOfTime {
	enum {MAX_UNITS = 5, DEFAULT_UNITS = 0}; //!> must
	enum {UOT_NONE, UOT_S, UOT_MS, UOT_US, UOT_PS}; //!> other similar enum

	static const char* uof[MAX_UNITS]; //!> must
};
const char* UnitOfTime::uof[MAX_UNITS] = {"", "s", "ms", "us", "ps"};


//! @todo ? Is Clock_Traits a good name ?
template<class T, int ut, typename UOT = UnitOfTime>
struct Clock_Traits {
	typedef T TimesType;
	static const char* utstr() {
		return UnitOfSelecter<ut, UOT>::struof;
	}
};

/** DefaultClock
	- using function <a>::clock<\a>() to count the time spending,
	not very reliable. 
	- should be runable on every environment.
	@relatesalso Clocker, Timer.
*/
struct DefaultClock : public Clock_Traits<clock_t, 
										  UnitOfTime::UOT_MS> {

	TimesType operator()() const {
		return ::clock() / CLOCKS_PER_SEC * 1000; // return ms.
	}
};


#ifdef WIN_PLATFORM
#include <windows.h>

struct WinClock : public Clock_Traits<double, 
									 UnitOfTime::UOT_MS> {

	TimesType operator()() const {
		LARGE_INTEGER count,persecond;
		::QueryPerformanceCounter( &count);
		::QueryPerformanceFrequency( &persecond);

		return (static_cast<double>( count.QuadPart) * 1000) / persecond.QuadPart; // get ms.
	}
};

#endif // WIN_PLATFORM


#endif // Clock_Head