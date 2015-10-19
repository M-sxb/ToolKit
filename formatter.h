// this file is under no license.
/** @file formatter.h
	@brief formatter classes.
	@date 10-7-2015 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-19-2015</b> 

	- builded this file.
*/


#ifndef Formatter_Head
#define Formatter_Head

// is plain old data
template<typename T>
struct IsPOD { enum {value = false};};

#define IS_POD(type) 			template<> struct IsPOD<type> { enum {value = true};}; 
#define IS_POD_E(extra,type) 	IS_POD(type) \
 								IS_POD(extra type)
// char
IS_POD_E(unsigned, char)
// short
IS_POD_E(unsigned, short)
// int
IS_POD_E(unsigned, int)
// long
IS_POD_E(unsigned, long)
// long long, vc 6.0 not support.
IS_POD_E(unsigned, long long)
// float
IS_POD(float)
// double
IS_POD(double)
// long double
IS_POD(long double)

/*
template<typename B, typename T>
struct ParamTypeImp { typedef typename ParamTypeImp<B::value, T>::type type;};

template<typename T>
struct ParamTypeImp<bool, T> { typedef T type;};
template<typename T>
struct ParamTypeImp<false, T> { typedef T const& type;};
template<typename T>
struct ParamTypeImp<false, T&> { typedef T const& type;};
*/
template<bool, typename T>
struct ParamTypeImp { typedef T type;};
template<typename T>
struct ParamTypeImp<false, T> { typedef T const& type;};
template<typename T>
struct ParamTypeImp<false, T&> { typedef T const& type;};

template<typename T>
struct ParamType : public ParamTypeImp<IsPOD<T>::value, T> { 
};

/* 
// vc 6.0 ok
template<bool>
struct Boolean { enum { value = true}};
template<>
struct Boolean<false> { enum { value = false}};

// vc 6.0 failed
template<bool, typename T>
struct ParamTypeImp { typedef T type;};
template<typename T>
struct ParamTypeImp<false, T> { typedef T const& type;};
template<typename T>
struct ParamTypeImp<false, T&> { typedef T const& type;};
*/

template<typename Info, typename Out>
struct Formatter {
	typedef typename ParamType<Info>::type InfoParam;
	typedef typename ParamType<Out>::type OutParam;
	virtual ~Formatter() {};
	virtual bool format(InfoParam info, OutParam out);
};



#endif // Formatter_Head