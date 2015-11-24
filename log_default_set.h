// this file is under no license.
/** @file log_default_set.h
	@brief log default setting classes.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-13-2015</b> 

	- builded this file.
	- add class LogLevel, class DefaultOutPuter, class DefaultDirection.
	- LogLevel::LevelEnum work with MFC at vc6.0 will case some macro problem, changed
	it's enum name.
	- add class MFCDirection, class TraceOutPuter, MsgBoxOutPuter.
*/


#ifndef Log_Default_Setting_Head
#define Log_Default_Setting_Head


#include "config.h"
#include "loghelp.h"


// user use
struct LogLevel {
	//!> must. 
	enum LevelEnum { Details, Debug, Info, Warn, Error,	Assert};
	
	//! must.
	template<class CharT>
	static const CharT* getName(LevelEnum level, CharT) {
		return name(level, CharT());
	}

private:
    template<class CharT>
    static const CharT* name(LevelEnum level, CharT) {
		static const CharT* name[] = {"Details", "Debug", "Info", 
									  "Warning", "Error", "Assert",
									  "Unknown"};
		size_t pos = static_cast<size_t>(level);
		size_t range =  sizeof(name) / sizeof(const CharT*);
		return name[pos >= range ? range - 1 : pos];
	}
	
    static const wchar_t* name(LevelEnum level, wchar_t) {
		static const wchar_t* name[] = {L"Details", L"Debug", L"Info", 
									    L"Warning", L"Error", L"Assert",
									    L"Unknown"};
	    size_t pos = static_cast<size_t>(level);
	    size_t range =  sizeof(name) / sizeof(const wchar_t*);
	    return name[pos >= range ? range - 1 : pos];
    }
};


// user use
/**
	@tparam CharT char type, like char, wchar_t
	@tparam Traits is a char traits
*/
template<class CharT, 
		 typename Traits>
struct OutPuter {
public:
    typedef typename Traits::OutCharT   OutCharT;
	typedef typename Traits::OutStream  OutStream;

	virtual ~OutPuter() {}

	virtual bool output(const OutStream& os) = 0;
};


#include <iostream> // std::cout, std::wcout


template<class CharT = char, 
		 typename Traits = Log_Char_Traits<CharT> >
class DefaultOutPuter : public OutPuter<CharT, Traits> {
public:
    typedef typename OutPuter<CharT, Traits>::OutCharT   OutCharT;
	typedef typename OutPuter<CharT, Traits>::OutStream  OutStream;

	virtual bool output(const OutStream& os) {
		output(os, OutCharT());
		return true;
	}

private:
    template<class Char>
    static void output(const OutStream& os, Char) {
        std::cout << os << std::endl;
	}
   
    static void output(const OutStream& os, wchar_t) {
        std::wcout << L"W: " << os << std::endl;
	}
};

// user use
/**
	@tparam LevelT log level type.
	@tparam CharT char type, like char, wchar_t.
	@tparam Traits is a log traits.
*/
template<typename LevelT, class CharT, typename Traits>
class DefaultDirection : public LogRedirect<LevelT, CharT, Traits> {
public:
    typedef typename LogRedirect<LevelT, CharT, Traits>::LevelE		LevelE;
	typedef typename LogRedirect<LevelT, CharT, Traits>::OutStream 	OutStream;
	typedef typename LogRedirect<LevelT, CharT, Traits>::Direction  Direction;

	virtual Direction redirect(LevelE le) { return 0;}
	virtual bool output(Direction direct, const OutStream& os) {
		return output_.output(os);
	};
	
private:
	DefaultOutPuter<CharT> output_;
};


#ifdef WORK_WITH_MFC

template<class CharT = TCHAR, 
		 typename Traits = Log_Char_Traits<CharT> >
class TraceOutPuter : public OutPuter<CharT, Traits> {
public:
    typedef typename OutPuter<CharT, Traits>::OutCharT   OutCharT;
	typedef typename OutPuter<CharT, Traits>::OutStream  OutStream;

	virtual bool output(const OutStream& os) {
		output(os, OutCharT());
		return true;
	}

private:
    template<class Char>
    static void output(const OutStream& os, Char) {
        TRACE(_T("%s\n"), os.c_str());
	}
   
    static void output(const OutStream& os, wchar_t) {
        TRACE(L"W: %s\n", os.c_str());
	}
};

#include <windows.h> // MessageBox

template<class CharT = TCHAR, 
		 typename Traits = Log_Char_Traits<CharT> >
class MsgBoxOutPuter : public OutPuter<CharT, Traits> {
public:
    typedef typename OutPuter<CharT, Traits>::OutCharT   OutCharT;
	typedef typename OutPuter<CharT, Traits>::OutStream  OutStream;

	virtual bool output(const OutStream& os) {
		output(os, OutCharT());
		return true;
	}

private:
    template<class Char>
    static void output(const OutStream& os, Char) {
        MessageBox(0, os.c_str(), "Error", MB_OK | MB_ICONERROR);
	}
   
    static void output(const OutStream& os, wchar_t) {
        MessageBox(0, os.c_str(), L"W: Error", MB_OK | MB_ICONERROR);
	}
};

class MFCDirection 
	: public LogRedirect<LogLevel, TCHAR, Log_Traits<LogLevel, TCHAR> > {
public:
	enum { DIRECTION_NONE, DIRECTION_TRACE, DIRECTION_MSG};

	typedef LogRedirect<LogLevel, TCHAR, Log_Traits<LogLevel, TCHAR> > Redirect;
	typedef Redirect::LevelE		LevelE;
	typedef Redirect::OutStream		OutStream;
	typedef LogLevel				LevelT;
	typedef Redirect::Direction     Direction;

	virtual Direction redirect(LevelE le) { 
#ifdef DEBUG_MODE
		if( le < LevelT::Error) return DIRECTION_TRACE;
		else return DIRECTION_MSG;
#else
		if( le < LevelT::Error) return DIRECTION_NONE;
		else return DIRECTION_MSG;
#endif
	}

	/** switch the output case. 
		direct == DIRECTION_TRACE using TraceOutPuter
		direct == DIRECTION_MSG using MsgBoxOutPuter
		direct == DIRECTION_NONE will not using any of outputer
	*/
	virtual bool output(Direction direct, const OutStream& os) {
		bool ret = true;
		switch(direct) {
		case DIRECTION_MSG:
			ret = msgbox_.output(os);
		case DIRECTION_TRACE:
			ret = trace_.output(os);
			break;
		default:
			ret = false;
		}
		return ret;
	};

private:
	TraceOutPuter<TCHAR> trace_;
	MsgBoxOutPuter<TCHAR> msgbox_;
};

#endif // WORK_WITH_MFC


#endif // Log_Default_Setting_Head