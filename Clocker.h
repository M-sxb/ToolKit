// this file is under no license.
/** @file Clocker.h
	@brief Clocker.h contains class of Clocker and any other inherited from it.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015<\b> 

	- builded this file.
	- add class Clocker, class FlatClocker, class FlatClocker2, class LoopClocker.
	- now only support \p char as char traits, when return the unit of time.
*/


#ifndef Clocker_Head
#define Clocker_Head


#include <climits>	// INT_MIN, INT_MAX
#include <cassert>  // assert


namespace timer {

/**
	template<typename Clock> class Clocker;
	<b>template Clock </b>

	- Type \em TimesType .
	- Function <em>static const char* utstr()</em>, which return the unit of time.

	@relatesalso Clock, Timer.
*/
template<typename C> 
class Clocker { 
public:
	typedef typename C::TimesType 	TimesType;
	typedef double						RetTimesType;
	typedef unsigned int 				RetCountType;

	Clocker() { 
		//! @todo add static assert on RetTimesType with TimesType, which is small or equal RetTimesType.
	}
	virtual ~Clocker() {}

	void begin() { 
		clocking(true);
	}

	void end() { 
		clocking(false);
	}

	virtual RetTimesType average() const { 
		if(counts() == 0) return 0;
		return total() / counts();
	}

	virtual RetTimesType total() const = 0;

	virtual RetCountType counts() const = 0;

	virtual bool clocking() const = 0;

	virtual void clocking(bool isClockOn) = 0; 

	static const char* utstr() { return Clock::utstr();}
};


//! 平坦计时器，记录最晚的begin()到最早的end()之间的耗时。
template<typename Clock> 
class FlatClocker : public Clocker<Clock> { 
public:
    typedef typename Clocker<Clock>::TimesType      TimesType;
	typedef typename Clocker<Clock>::RetTimesType   RetTimesType;
	typedef typename Clocker<Clock>::RetCountType   RetCountType;

	FlatClocker() : tmptime(0), isClocking(false) {}

	virtual RetTimesType average() const {
		return total();
	}

	virtual RetTimesType total() const { 
		if(clocking()) return Clock()() - tmptime;
		else return tmptime;
	}

	virtual RetCountType counts() const { 
		return clocking() ? 1 : 0;
	} 

	virtual bool clocking() const { return isClocking;} 

	virtual void clocking(bool isClockOn) { 
		if( !clocking() && !isClockOn) return ; // blocking the end() call if already clock off.

		if( isClockOn) tmptime = Clock()();
		else tmptime = Clock()() - tmptime;
		isClocking = isClockOn;
	} 

private:
	TimesType tmptime;
	bool isClocking;
};


//! 平坦计时器，记录最早的 begin()到最早的end()之间的耗时。
template<typename Clock> 
class FlatClocker2 : public Clocker<Clock> { 
public:
    typedef typename Clocker<Clock>::TimesType      TimesType;
	typedef typename Clocker<Clock>::RetTimesType   RetTimesType;
	typedef typename Clocker<Clock>::RetCountType   RetCountType;

	FlatClocker2() : tmptime(0), isClocking(false) {}

	virtual RetTimesType average() const {
		return total();
	}

	virtual RetTimesType total() const { 
		if(clocking()) return Clock()() - tmptime;
		else return tmptime;
	}

	virtual RetCountType counts() const { 
		return clocking() ? 1 : 0;
	} 

	virtual bool clocking() const { return isClocking;} 

	virtual void clocking(bool isClockOn) {
		if( clocking() && isClockOn) return ; // blocking the begin() call if already clock on.
		if( !clocking() && !isClockOn) return ; // blocking the end() call if already clock off.

		if( isClockOn) tmptime = Clock()();
		else tmptime = Clock()() - tmptime;
		isClocking = isClockOn;
	} 

private:
	TimesType tmptime;
	bool isClocking;
};


//! 循环计时器
/** LoopClocker's counts must smaller than INT_MAX
*/
template<typename Clock> 
class LoopClocker : public Clocker<Clock> {
	enum { COUNT_MASK = INT_MIN};
public:
    typedef typename Clocker<Clock>::TimesType      TimesType;
	typedef typename Clocker<Clock>::RetTimesType   RetTimesType;
	typedef typename Clocker<Clock>::RetCountType   RetCountType;

	LoopClocker() : totaltimes(0), calledcounts(0), tmptime(0) {}

	virtual RetTimesType average() const { 
		RetTimesType count = counts();
		if( count == 0) return 0;
		if(clocking() && count > 1) return totaltimes / (count - 1);
		else return total() / count;
	}

	virtual RetTimesType total() const { 
		if(clocking()) return totaltimes + Clock()() - tmptime;
		return totaltimes;
	}

	virtual RetCountType counts() const {	return calledcounts & ~COUNT_MASK;}

	virtual bool clocking() const {	return !(!(calledcounts & COUNT_MASK));}

	virtual void clocking(bool isClockOn) { 
		if( clocking() && isClockOn) return ;// blocking the begin() call if already clock on.
		if( !clocking() && !isClockOn) return ; // blocking the end() call if already clock off.

		if( isClockOn) { 
			tmptime = Clock()();
			calledcounts = calledcounts | COUNT_MASK;
			assert(counts() <= INT_MAX - 1);
			++calledcounts;
		} else { 
			tmptime = Clock()() - tmptime;
			totaltimes += tmptime;
			tmptime = 0;
			calledcounts = calledcounts & ~COUNT_MASK;
		}
	}

private:
	TimesType totaltimes;
	RetCountType calledcounts;
	TimesType tmptime;
};

} // namespace timer.


#endif // Clocker_Head