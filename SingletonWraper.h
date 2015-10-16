// this file is under no license.
/** @file SingletonWraper.h
	@brief singleton wraper using for build sample singleton.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add class SingletonWraper.
*/


#ifndef SingletonWraper_Head
#define SingletonWraper_Head

/** SingletonWraper<T>, to make type T a singleton type.
	This singleton may be a phoenix singleton depends on the implementation of 
	static type. See more on "Moden C++ Designe" charpter ?.
*/
template<typename T> 
class SingletonWraper {
	SingletonWraper() {}
	SingletonWraper( const SingletonWraper&);
	SingletonWraper& operator=(const SingletonWraper&);
public:
	typedef T type;
	
	static T& instance() {
		static T t;
		return t;
	}
};


#endif // SingletonWraper_Head