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
	- add class Formatter.
*/


#ifndef Formatter_Head
#define Formatter_Head


#include <string>


/*
#define CLONE_IMP(base, derived) 	virtual base* clone() const { \
										derived* ptr = new derived(*this); \
										return ptr; \
									}
*/


//! this is a weak formatter.
struct Formatter { 
	virtual ~Formatter() {}

	/** clone this Formatter.
		@return this Formatter.
	*/
//	virtual Formatter* clone() const = 0;

	/** add format string to output string.
		@param[in] info info class.
		@param[out] out output string.
		@retval true formated.
		@retval fasle not formated, or failed.
	*/
	virtual bool format(std::string& out) const = 0;
};


#endif // Formatter_Head