// this file is under no license.
/** @file log.h
	@brief LogImp class.
	@date 10-7-2015 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-12-2015</b> 

	- builded this file.
	- add class LogLevel, class DefaultOutPuter, class DefaultDirection, class LogImp.

	<b>10-13-2015</b> 
	
	- LogLevel::LevelEnum work with MFC at vc6.0 will case some macro problem, changed
	it's enum name.
	- move class LogLevel, class DefaultOutPuter, class DefaultDirection to file 
	log_default_set.h
	- add singleton wraper cnslLog, wcnslLog, mfcLog
	- add macros LOGIMP, LOG
	- change LOG macros to LOGS macros, add defLog type, LOG macros
	- VC6.0 basically OK.
*/


#ifndef Log_Head
#define Log_Head


#include "config.h"
#include "loghelp.h"
#include "log_default_set.h"
#include "SingletonWraper.h"

// LogImp
template<typename LevelT,
		 class CharT,
		 typename Traits,
		 typename Formater, 
		 typename Fileter,
		 typename Directer>
class LogImp;

// log singleton wraps
typedef SingletonWraper< LogImp<
                            LogLevel, char, 
							Log_Traits<LogLevel, char>, 
							LogFormater<LogLevel, char, Log_Traits<LogLevel, char> >,
							LogFilter<LogLevel>,
							DefaultDirection<LogLevel, char, Log_Traits<LogLevel, char> > 
							>
						> cnslLog;

typedef SingletonWraper< LogImp<
                            LogLevel, wchar_t, 
							Log_Traits<LogLevel, wchar_t>, 
							LogFormater<LogLevel, wchar_t, Log_Traits<LogLevel, wchar_t> >,
							LogFilter<LogLevel>,
							DefaultDirection<LogLevel, wchar_t, Log_Traits<LogLevel, wchar_t> > 
							>
						> wcnslLog;

#ifdef WORK_WITH_MFC
typedef SingletonWraper< LogImp<
                            LogLevel, TCHAR, 
							Log_Traits<LogLevel, TCHAR>, 
							LogFormater<LogLevel, TCHAR, Log_Traits<LogLevel, TCHAR> >,
							LogFilter<LogLevel>,
							MFCDirection 
							>
						> mfcLog;
#endif // WORK_WITH_MFC


// default log singleton
#ifdef WORK_WITH_MFC
typedef mfcLog defLog;
#else 
typedef cnslLog defLog;
#endif // WORK_WITH_MFC


// LOGIMP macros
#define LOGIMP(logimp, loglevel, msg)		logimp((loglevel), (msg));
#define LOGIMP_B(logimp, loglevel, b, msg)	logimp((loglevel), !(!(b)), (msg));
#define LOGIMP_DETAILS(logimp, msg)			logimp.details((msg));
#define LOGIMP_DEBUG(logimp, msg)			logimp.debug((msg));
#define LOGIMP_INFO(logimp, msg)			logimp.info((msg));
#define LOGIMP_WARN(logimp, msg)			logimp.warn((msg));
#define LOGIMP_ERROR(logimp, msg)			logimp.error((msg));
#define LOGIMP_ASSERT(logimp, b, msg)		logimp.assert(!(!(b)), (msg));


// LOG singleton macros
#define LOGS(loger, loglevel, msg)			LOGIMP(loger::instance(), loglevel, msg);
#define LOGS_B(loger, loglevel, b, msg)		LOGIMP_B(loger::instance(), loglevel, b, msg);
#define LOGS_DETAILS(loger, msg)			LOGIMP_DETAILS(loger::instance(), msg);
#define LOGS_DEBUG(loger, msg)				LOGIMP_DEBUG(loger::instance(), msg);
#define LOGS_INFO(loger, msg)				LOGIMP_INFO(loger::instance(), msg);
#define LOGS_WARN(loger, msg)				LOGIMP_WARN(loger::instance(), msg);
#define LOGS_ERROR(loger, msg)				LOGIMP_ERROR(loger::instance(), msg);
#define LOGS_ASSERT(loger, b, msg)			LOGIMP_ASSERT(loger::instance(), msg);


// LOG singleton macros
#define LOG(loglevel, msg)			LOGS(defLog, loglevel, msg);
#define LOG_B(loglevel, b, msg)		LOGS_B(defLog, loglevel, b, msg);
#define LOG_DETAILS(msg)			LOGS_DETAILS(defLog, msg);
#define LOG_DEBUG(msg)				LOGS_DEBUG(defLog, msg);
#define LOG_INFO(msg)				LOGS_INFO(defLog, msg);
#define LOG_WARN(msg)				LOGS_WARN(defLog, msg);
#define LOG_ERROR(msg)				LOGS_ERROR(defLog, msg);
#define LOG_ASSERT(b, msg)			LOGS_ASSERT(defLog, msg);


/**
	@todo Work out the LogImp.
	<em>LogLevel -> Formater -> Fileter</em> but now is : <em>LogLevel -> Fileter</em>
	<em>InStream -> Formater -> OutStream -> Directer -> OutPut</em>
*/
template<typename LevelT,
		 class CharT,
		 typename Traits,
		 typename Formater, 
		 typename Fileter,
		 typename Directer>
class LogImp {
public:
	typedef typename Traits::LevelE		LevelE;
	typedef typename Traits::InCharT	InCharT;
	typedef typename Traits::OutStream	OutStream;
	
	
	virtual ~LogImp() {
		// vc6.0: this function does not been called.
		// LOG_ERROR(mfcLog, _T("what the"));
		// vc6.0: this function called once and return.
		// LOG_ERROR(cnslLog, "what the");
	}

	void log(LevelE le, const InCharT* msg) { 
		OutStream os;
		os += formater_.getEnumName(le);
		formater_.format(msg, os);
		output(le, os);
	}
	
	void details(const InCharT* msg) {
		log(LevelT::Details, msg);
	}

	void debug(const InCharT* msg) {
		log(LevelT::Debug, msg);
	}

	void info(const InCharT* msg) {
		log(LevelT::Info, msg);
	}

	void warn(const InCharT* msg) {
		log(LevelT::Warn, msg);
	}

	void error(const InCharT* msg) {
		log(LevelT::Error, msg);
	}

	void assert(bool isOk, const InCharT* msg) {
		if(isOk) return ;
		log(LevelT::Assert, msg);
	}


	void operator()(LevelE level, const InCharT* msg) {
		log(level, msg);
	}

	/*! \param[in] isOk check the express is false, which will output it's message.
	*/
	template<class T>
	void operator()(LevelE level, T isOk, const InCharT* msg) {
		if(isOk) return ;
		log(level, msg);
	}
	
protected:
	virtual bool output(LevelE le, const OutStream& os) { 
		if( fileter_.filter(le)) return false;
		return directer_.output(directer_.redirect(le), os);
	}

private:
	Formater formater_;
	Fileter fileter_;
	Directer directer_;
};


#endif // Log_Head