// this file is under no license.
/** @file formatter.h
	@brief formatter classes.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-19-2015</b> 

	- builded this file.
*/


#ifndef Formatter_Head
#define Formatter_Head

#include <string>

/*
template<typename Info, typename Out>
struct Formatter {
	typedef typename ParamType<Info>::type InfoParam;
	typedef typename ParamType<Out>::type OutParam;
	virtual ~Formatter() {};
	virtual bool format(InfoParam info, OutParam out) = 0;
};

template<typename Info, typename Out>
class AggregateFormatter : public Formatter<Info, Out> { 
	typedef typename std::vector<std::share_ptr<Formatter<Info, Out> > > Container;
	typedef typename Container::iterater	iterater;

	void addFormatter(const std::share_ptr<Formatter<Info, Out> >& ptr) { 
		vformater_.push_back(ptr);s
	}
	virtual bool format(InfoParam info, OutParam out) { 
		bool result = false;
		iterater iter = vformater_.begin();
		while(iter != vformater_.end()) { 
			result = *iter->formater(info, out);
			++iter;
		}
		return result;
	}
public:
	std::vector<std::share_ptr<Formatter<Info, Out> > > vformater_;
};
*/
struct LogPointInfo { 
	virtual ~LogPointInfo() {}
};

#define CLONE_IMP(base, derived) 	virtual base* clone() const { \
										derived* ptr = new derived(*this); \
										return ptr; \
									}

struct Formatter { 
	virtual ~Formatter() {}

	/** clone this Formatter.
		@return this Formatter.
	*/
	virtual Formatter* clone() const = 0;

	/** add format string to output string.
		@param[in] info info class.
		@param[out] out output string.
		@retval true formated.
		@retval fasle not formated, or failed.
	*/
	virtual bool format(const LogPointInfo& info, std::string& out) const = 0;
};

struct PadFormatter : public Formatter { 
	PadFormatter(size_t n = 0, char pad = ' ') : n_(n), pad_(pad) {}

	void setData(size_t n, char pad = ' ') { n_ = n; pad_ = pad;}

	CLONE_IMP(Formatter, PadFormatter)

	virtual bool format(const LogPointInfo& info, std::string& out) const { 
		size_t n = n_;
		while(n--) { 
			out += pad_;
		}
		return true;
	}

	size_t n_;
	char pad_;
};

class FormatBuilder { 
	virtual ~FormatBuilder() {}
	virtual bool handleFormatStr(const std::string& fstr, std::string& out) { 
		
	}
};




#endif // Formatter_Head