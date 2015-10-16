// this file is under no license.
/** @file loghelp.h
	@brief log help class.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-12-2015</b> 

	- builded this file.
	- add class Log_Traits, class LogFormater, class LogFilter, class LogRedirect
	- test add LogFormatAttr.

   <b>10-13-2015</b> 
   - add Log_Char_Traits

	<b>10-15-2015</b> 
	- add templary use class LogFormatAttr
*/


#ifndef LogHelp_Head
#define LogHelp_Head

#include "config.h"
#include <string>


template<class Char = char>
struct Log_Char_Traits {
	typedef Char	CharT; //!> not using right now
	typedef CharT	InCharT;
	typedef CharT	OutCharT;
	typedef typename std::basic_string<InCharT> InStream;
	typedef typename std::basic_string<Char> 	OutStream;
};

template<typename LevelT, class Char = char>
struct Log_Traits : public Log_Char_Traits<Char> {
	typedef typename Log_Char_Traits<Char>::InCharT InCharT;
	typedef typename Log_Char_Traits<Char>::OutCharT OutCharT;
	typedef typename Log_Char_Traits<Char>::InStream InStream;
	typedef typename Log_Char_Traits<Char>::OutStream OutStream;
	typedef typename LevelT::LevelEnum	LevelE;
};


//! this is templary class.
template<typename CharT>
struct LogFormatAttr {
	typedef Log_Char_Traits<CharT> Traits;
	typedef typename Traits::OutCharT 	Char;
	typedef typename Traits::OutStream 	OutStream; //!> have char type \a OutCharT
	
    LogFormatAttr() {
        fs_ = "$Msg$\n";
		septor_ = '$';
    }

    OutStream formatStr() const { return fs_;}
	void formatStr(const OutStream& nfs) { fs_ = nfs;}
	Char separator() const { return septor_;}
	void separator(Char c) { septor_ = c;}

    OutStream fs_;
	Char septor_;
};

template<>
struct LogFormatAttr<wchar_t> {
	typedef Log_Char_Traits<wchar_t> Traits;
	typedef Traits::OutCharT 	Char;
	typedef Traits::OutStream 	OutStream; //!> have char type \a OutCharT
	
	LogFormatAttr() {
        fs_ = L"$Msg$\n";
		septor_ = L'$';
    }

    OutStream formatStr() const { return fs_;}
	void formatStr(const OutStream& nfs) { fs_ = nfs;}
	Char separator() const { return septor_;}
	void separator(Char c) { septor_ = c;}

    OutStream fs_;
	Char septor_;
};


//! @todo need a better logFormater
template<typename LevelT, typename CharT, typename Traits>
class LogFormater { 
public:
	typedef typename Traits::LevelE		LevelE;
	typedef typename Traits::InCharT 	InCharT;
	typedef typename Traits::OutStream 	OutStream;
	
	LogFormater() { }
	virtual ~LogFormater() {}

	virtual void format(const InCharT* msg, OutStream& os) { 
		//! @todo imply this function.
		os += msg;
	}

//	OutStream formatStr() const { return attr_.formatStr();}
//	void formatStr(const OutStream& nfs) { attr_.formatStr(nfs);}
//	CharT separator() const { return attr_.separator();}
//	void separator(CharT c) { attr_.separator(c);}

	static const CharT* getEnumName(LevelE level) {
		return LevelT::getName(level, CharT());
	}
protected:
	/** formating string by Format.
		@param[in] fs formatStr that for Format.
		@param[out] os outstream that have formated string if return true.
		@retval true formated.
		@retval false not formated this Format.
	*/
	virtual bool formating(const OutStream& fs, OutStream& os) {
		//! @todo imply this function.
		return true;
	}
	
private:
    LogFormatAttr<CharT> attr_;
};


template<typename LevelT> 
class LogFilter {
public:
	typedef typename LevelT::LevelEnum LevelE;

	virtual ~LogFilter() {}

	/** filter the log level.
		@param[in] le log level.
		@retval true filter this log level.
		@retval false otherwise.
	*/
	virtual bool filter(LevelE le) { return false;}
};


//! redirect the output stream to other outputer
template<typename LevelT, class CharT, typename Traits>
class LogRedirect {
public:
	typedef typename Traits::LevelE		LevelE;
	typedef typename Traits::OutStream 	OutStream;
	typedef int Direction;

	virtual ~LogRedirect() {}
	virtual Direction redirect(LevelE le) = 0;
	virtual bool output(Direction direct, const OutStream& os) = 0;
};

#endif // LogHelp_Head