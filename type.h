// this file is under no license.
/** @file type.h
	@brief type namespace, contains ParamType, IsPOD, and others.
	@date 10-7-2015 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-20-2015</b> 

	- builded this file.
	- add IsPOD<T>.
	- add ParamType<T>.
*/


#ifndef Type_Namespace_Head
#define Type_Namespace_Head


namespace type { 


namespace details {
	struct true_ {};
	struct false_ {};

	// vc 6.0 ok
	template<bool>
	struct bool_ { enum { value = true}; typedef true_ type;};
	template<>
	struct bool_<false> { enum { value = false}; typedef false_ type;};
} // namespace details


// is plain old data
template<typename T>
struct IsPOD { enum {value = false}; typedef details::false_ type;};

#define IS_POD(t) 				template<> struct IsPOD<t> { enum {value = true}; typedef details::true_ type;}; 
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
// IS_POD_E(unsigned, long long)
// float
IS_POD(float)
// double
IS_POD(double)
// long double
IS_POD(long double)


namespace details { 
/*
// vc 6.0 failed
template<bool, typename T>
struct ParamTypeImp { typedef T type;};
template<typename T>
struct ParamTypeImp<false, T> { typedef T const& type;};
template<typename T>
struct ParamTypeImp<false, T&> { typedef T const& type;};

template<typename T>
struct ParamType : public ParamTypeImp<IsPOD<T>::value, T> {};
*/

template<typename Bool, typename Type>
struct ParamTypeImp { 
	template<typename B, typename T>
	struct apply {
		typedef T type;
	};

	template<typename T>
	struct apply<details::false_, T> {
		typedef T const& type;
	};

	template<typename T>
	struct apply<details::false_, T&> {
		typedef T const& type;
	};

	typedef typename apply<typename Bool::type, Type>::type type;
};
} // details namespace

//! todo get type T's pure type.
template<typename T>
struct ParamType : public details::ParamTypeImp<IsPOD<T>, T> {};


} // namespace type


#endif // Type_Namespace_Head