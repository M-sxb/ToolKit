// this file is under no license.
/** @file format.h
	@brief formatter class's.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-22-2015</b> 

	- builded this file.
*/


#ifndef Details_Formatter_Head
#define Details_Formatter_Head


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

namespace detatils {

struct AlignFormatter { 
	/** align formatter
		@param[in] fstr format string, like .2, -12.2.
		@param[in] cstr content string.
		@param[out] out output string.
		@retval true formated.
		@retval false failed, and not formated. 
	*/
	static bool format(const std::string& fstr, const std::string& cstr, std::string& out) {
		return false; 
	}
};


} // details namespace


#endif // Format_Head