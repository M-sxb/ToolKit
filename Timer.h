// this file is under no license.
/** @file Timer.h
	@brief Timer.h contains class of Timer and any other .
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add class Timer.
	- add type CountTimer.
*/


#ifndef Timer_Head
#define Timer_Head


#include <string> // std::basic_string<>
#include <sstream> // 

#include "log.h"   // put log.h file here for avoid assert definition conflict.
#include "Clock.h" // Clock
#include "Clocker.h" // Clocker


namespace timer {

namespace details {

template<class CharT>
struct TimerStr {
	std::basic_string<CharT> msg_;
	TimerStr(const CharT* msg = 0) : msg_(msg ? msg : "") {}
};


template<>
struct TimerStr<wchar_t> {
	std::basic_string<wchar_t> msg_;
	TimerStr(const wchar_t* msg = 0) : msg_(msg ? msg : L"") {}
};

} // namespace details

/** Simple timer.
	- char traits type not complate(Only support char).
	- can only running on console environment.
	- the type \em CountTimer is class Time<FlatClocker, char> type.

	@relatesalso Clock, Clocker.
*/
template<typename Clocker, class CharT = char>
class Timer { 

public:
	Timer(const CharT* msg = 0) : msg_(msg ? msg : "") { 
		clocker_.begin();
	}
	~Timer() { 
		clocker_.end();
		print();
	}

private:
	void print() { 
		std::basic_ostringstream<CharT> oss;
	//	size_t prection = oss.precision(3);
		if(msg_.size()) oss << msg_ << ": " << clocker_.average() << clocker_.utstr();
		else oss << clocker_.average() << clocker_.utstr();
		std::basic_string<CharT> str= oss.str();
		LOG_INFO(str.c_str());
	} 
	
//	TimerStr<CharT> msg_;
	std::basic_string<CharT> msg_;
	Clocker clocker_;
};


#ifdef WIN_PLATFORM
typedef Timer<FlatClocker<WinClock> > CountTimer;
#else
typedef Timer<FlatClocker<DefaultClock> > CountTimer;
#endif // WIN_PLATFORM

} // namespace timer.

#endif // Timer_Head
