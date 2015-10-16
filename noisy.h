// this file is under no license.
/** @file noisy.h
	@brief noisy.h is a test kit, using for test ctor, dtor and copy, move.
	@date 
	@version
	@authors
	@attention This class is file under modification, and when you use it should
	use Noisy namespace.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add class Base, class Dervied
	- this file can only running on console environment.
*/


#ifndef Noisy_Head
#define Noisy_Head

#include <iostream> // std::cout.

namespace Noisy { 

class Base {
	char c_;
public:
	Base(char c = 'B') : c_(c) {
		std::cout << "Base::Base() : " << c_ << std::endl;
	}
	virtual ~Base() {
		std::cout << "Base::~Base() : " << c_ << std::endl;
	}
	
	Base(const Base& b) : c_(b.c_) {
		std::cout << "Base::Base(const Base&) : " << c_ << std::endl;
	}

	virtual Base& operator=(const Base& b) {
		std::cout << "Base::operator=() : " << c_  << " <= " << b.c_ << std::endl;
		c_ = b.c_;
		return *this;
	}

	virtual Base* vfun() {
		std::cout << "Base::vfun() const : " << c_ << std::endl;
		return this;
	}
};

class Derived : public Base {
public:
	Derived(char c = 'D') : Base(c)  {
		std::cout << "Derived::Derived()" << std::endl;
	}
	virtual ~Derived() {
		std::cout << "Derived::~Derived()" << std::endl;
	}
	
	Derived(const Derived& d) {
		std::cout << "Derived::Derived(const Derived&)" << std::endl;
	}

	virtual Derived& operator=(const Derived& d) {
//		Base::operator=(d); 
		std::cout << "Derived::operator=()" << std::endl;
		return *this;
	}

	virtual Base* vfun() { 
		// vc 6.0 error c2555 virtual Derived* vfun()
		std::cout << "Base::vfun() const" << std::endl;
		return this;
	}
};

} // namespace Noisy


#endif // Noisy_Head