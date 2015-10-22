// this file is under no license.
/** @file logpoint_info.h
	@brief LogPointInfo classes.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-22-2015</b> 

	- builded this file.
	- add class LogPointInfo, class MappedLogPointInfo, class AggregateLogPointInfo.
*/


#ifndef LogPointInfo_Head
#define LogPointInfo_Head


#include <string>
#include <vector>
#include <map>
	

struct Formatter; 
struct LogPointInfo;


struct LogPointInfo { 
	typedef Formatter* FormatterPtr; //! @todo replace it by smart ptr.
	virtual ~LogPointInfo() {}

	/** add format string to output string.
		@param[in] in input string that contain format string.
		@param[out] out output string.
		@retval true parse ok.
		@retval fasle not parsed, or failed.
	*/
	bool parse(const std::string& in, std::string& out) { 
		return false;
	}
protected:

	/** get formater pointer
		@param[in] fstr format string.
		@return formatter pointer, or failed 0/null_ptr.
	*/
	virtual FormatterPtr getFormatter(const std::string& fstr) = 0;
};
s
namespace details { 

template<typename C>
void release(C& c) { 
	typedef typename C::iterater Iter;
	Iter iter = c.begin();
	while(iter != c.end()) { delete *iter; ++iter;} 
}

} // details namespace

class MappedLogPointInfo : public LogPointInfo { 
	typedef std::map<std::pair<std::string, FormatterPtr> > MapType;

public:
	virtual ~MappedLogPointInfo() { 
		details::release(map_);//! @todo remove this function when using smartptr for Formatter.
	}

	void addFormater(const std::string& fstr, FormatterPtr pformatter) { 
		map_[fstr] = pformatter;
	}

protected:
	virtual FormatterPtr getFormatter(const std::string& fstr) { 
		if( map_.find(fstr) != map_.end()) return map_[fstr];
		return FormatterPtr(0);
	}

private:
	MapType map_;
};

class AggregateLogPointInfo : public LogPointInfo { 
	typedef LogPointInfo* 					LogPointInfoPtr //! @todo replace it by smart ptr.
	typedef std::vector<LogPointInfoPtr> 	VecType;
	typedef VecType::iterater 				VecIter;

public:
	virtual ~MappedLogPointInfo() { 
		details::release(vec_); //! @todo remove this function when using smartptr for LogPointInfo.
	}

	void addLogPointInfo(LogPointInfoPtr ploginfo) { 
		vec_.push_back(ploginfo);
	}

protected:
	virtual FormatterPtr getFormatter(const std::string& fstr) { 
		VecIter iter = vec_.begin();
		while( iter != vec_.end()) { 
			FormatterPtr pf = (*iter).getFormatter(fstr);
			if(!(!pf))	return pf; // if pf is not null.
		}
		return FormatterPtr(0);
	}

private:
	VecType vec_;
};


#endif // LogPointInfo_Head