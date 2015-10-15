### ToolKit
> Notic: this kit is still at modification.  

#### Works fine with

- VC 6.0
- VS 2010
- MinGW 4.8.0(part)

#### Main classes in the Kit

- LogImp
- Newer
- SmartPtr
- Timer

#### Test example
```C++
/** @file test.cpp
	@brief test toolkit
*/


#include <iostream>
#include "../Toolkit/log.h"


//! test cnslLog. console log
static void testOne() {
	cnslLog::type& log = cnslLog::instance();
	log.debug("What this message is?");
	log.details("Ok, what are you doing?");
	log.assert( sizeof(log) != sizeof(cnslLog), "assert error!");
	log(LogLevel::Info, "What if ");
	log(LogLevel::Details, "this is a detail");
	log(LogLevel::Error, sizeof(log) == sizeof(cnslLog), "this is a what");
	log.warn("Haha ha ha");

	char* p = 0;
	log(LogLevel::Error, p, "this is a what");
}

//! test wcnslLog. wchar_t console log
static void testOne_2() {
	wcnslLog::type& log = wcnslLog::instance();
	log.debug(L"What this message is?");
	log.details(L"Ok, what are you doing?");
	log.assert( sizeof(log) != sizeof(wcnslLog), L"assert error!");
	log(LogLevel::Info, L"What if ");
	log(LogLevel::Details, L"this is a detail");
	log(LogLevel::Error, sizeof(log) == sizeof(wcnslLog), L"this is a what");
	log.warn(L"Haha ha ha");

	char* p = 0;
	log(LogLevel::Error, p, L"this is a what");
}



#include "../Toolkit/Timer.h"

//! test for Timer, Clocker.
static void testTwo() {
	typedef std::string::const_iterator citerator;

	CountTimer ct;

#ifdef WIN_PLATFORM
	FlatClocker2<WinClock> fc2;
    LoopClocker<WinClock> lc;
#else
	FlatClocker2<DefaultClock> fc2;
    LoopClocker<DefaultClock> lc;
#endif // WIN_PLATFORM

	fc2.begin();
	std::string fs_("asdfsadf$Msg$$$Msg$dd$$");
	char septor_ = '$';
	std::string os;
	citerator iter = fs_.begin();
	while(iter != fs_.end()) {
		lc.begin();
		if(*iter != septor_) {
			os.append(1, *iter);
			++iter;
		} else {
			size_t leftpos = iter - fs_.begin();
			size_t reightpos = fs_.find(septor_, leftpos+1);
			if( reightpos == -1) break;
			std::string slicefs(fs_, leftpos+1, reightpos-leftpos-1);
			iter = fs_.begin() + reightpos + 1;
		}
		lc.end();
	}
	fc2.end();

	std::cout << fc2.average() << fc2.utstr() << std::endl;
	std::cout << os << std::endl;
	std::cout << lc.average() << lc.utstr() << " " 
			  << lc.total() << lc.utstr() << " " 
			  << lc.counts() << std::endl;
}


#include "../Toolkit/Newer.h"

class TestNewer : public Newer {
	int a_;
public:
	TestNewer() { }
	virtual ~TestNewer() {}
};

//! test for Newer.
static void testThree() {

	std::cout << sizeof(TestNewer[10]) << std::endl;
	std::cout << sizeof(TestNewer) * 10 << std::endl;

//	Newer* p = new TestNewer[10]; 	// @attention not work with MinGW
//	delete[] p; 					//! @attention not work with MinGW

	Newer* p3 = new TestNewer;
	delete p3;

	Newer* p4 = Newer::allocate(1, p3);
	Newer::deallocate(p4);
}


#include "../Toolkit/SmartPtr.h"

struct CMyPoint {
	double x, y;
	CMyPoint(double xx, double yy) : x(xx), y(yy) {}
};

//! test for SmartPtr.
static void testFour() {
	CountTimer ct;
	CMyPoint* p1 = new CMyPoint(10.0, 20.0);
	CMyPoint* p2 = new CMyPoint(20.0, 30.0);
	CMyPoint* p3 = new CMyPoint(30.0, 40.0);

	SmartPtr<CMyPoint> sp1(p1), sp2(p2), sp3(p3), sp0(0);
	SmartPtr<CMyPoint> sp4(sp1), sp5(sp1), sp6(sp2);

	if(!sp0) std::cout << "sp0 is NULL\n" << std::endl;
	if(!sp1) std::cout << "sp1 is NULL\n" << std::endl;
	
	sp0 = sp3;
	sp3 = sp1;
	CMyPoint* ptr = sp6.get();
	CMyPoint* ptr2 = getPtr(sp5);
	sp4.reset(0);
	resetPtr(sp1);
	resetPtr(sp1);
	resetPtr(sp5);
	
	double x = sp0->x;
	double y = sp0->y;
	x = (*sp3).x;
	y = (*sp6).y;
}


int main() {
	testOne(); 		// log
	testOne_2(); 	// wlog
	testTwo(); 		// Timer
	testThree(); 	// Newer
	testFour(); 	// SmartPtr

	std::cout << "Press any button to continue..." << std::endl;
	std::cin.get();
	return 0;
}
```
