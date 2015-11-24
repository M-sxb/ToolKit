// this file is under no license.
/** @file test_suit.h
	@brief test_suit.h contains class or function using for test, No.01.
	@date  15-11-2015
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>Notice<\b> 

	- for operator test function: 	
		1. int, unsigned int tested, passed.
		2. unsigned char tested(at 2,4), not pass.
		3. dont trust when using float or double type.
	- for Int, Uint struct.
		1. Int or Uint can single use.
		2. can use Int to initialize the Uint, Uint convert to 
		Int must call toUint() function.

	<b>15-11-2015<\b> 

	- builded this file.
	- add operator test function(+, -, *, /).
	- add equal like test function( isequal, isbig, isless)
	- add struct Int, struct Uint
	- using THROW_EXCEPTION macro to throw exception.
	- add std::numeric_limits<Int>(which inherited from td::numeric_limits<int>)
	to namespace std.
	- add std::numeric_limits<Uint>(which inherited from td::numeric_limits<unsigned int>)
	to namespace std.
	- add operator<<, operator>> for iostream.
	- change THROW_EXCEPTION to NOT_THROW_EXCEPTION. Default is throw exception
	- MinGW g++ 4.8.0 ok, VC 6.0 ok.

	@example
	@code
	#include <iostream>
	#include "test_suit.h"

	const char* print_trueOrFalse(bool b) { 
		static const char* str_true = "true";
		static const char* str_false = "false";
		return b ? str_true : str_false;
	}

	template<typename T> 
	void testOne_Hepler(T lhs, T rhs) { 
		std::cout << "test operator with " << lhs << " and " << rhs << "." << std::endl; 
		std::cout << "\t + :" << print_trueOrFalse(test::isadd_ok(lhs, rhs)) << std::endl;
		std::cout << "\t - :" << print_trueOrFalse(test::issub_ok(lhs, rhs)) << std::endl;
		std::cout << "\t * :" << print_trueOrFalse(test::ismult_ok(lhs, rhs)) << std::endl;
		std::cout << "\t / :" << print_trueOrFalse(test::isdiv_ok(lhs, rhs)) << std::endl;
		std::cout << std::endl;
	}

	#include <typeinfo>

	template<typename T>
	static void testOne_Heper2() {
		T zero = 0;
		T max = std::numeric_limits<T>::max();
		T min = std::numeric_limits<T>::min();
		std::cout << "test type: " << typeid(T).name() << std::endl;
		testOne_Hepler(zero, zero);
		testOne_Hepler(zero, max);
		testOne_Hepler(zero, min);
		testOne_Hepler(max, max);
		testOne_Hepler(max, min);
		testOne_Hepler(min, min);
	}

	// test for operator.
	static void testOne() { 
		// int, unsigned int tested, passed.
		// unsigned char tested(at 2,4), not pass.
		// dont trust when using float or double type.
		typedef float test_type;
		testOne_Heper2<test_type>();
	}

	template<typename T>
	static void testTwo_Helper(const T& lhs, const T& rhs) {
		std::cout << lhs << " compare to " << rhs << std::endl;
		std::cout << " lhs < rhs " << print_trueOrFalse(lhs < rhs) << std::endl;
		std::cout << " lhs <= rhs " << print_trueOrFalse(lhs <= rhs) << std::endl;
		std::cout << " lhs > rhs " << print_trueOrFalse(lhs > rhs) << std::endl;
		std::cout << " lhs >= rhs " << print_trueOrFalse(lhs >= rhs) << std::endl;
		std::cout << " lhs isequal rhs " << print_trueOrFalse(test::isequal(lhs, rhs)) << std::endl;
		std::cout << " lhs == rhs " << print_trueOrFalse(lhs == rhs) << std::endl;
		std::cout << " lhs != rhs " << print_trueOrFalse(lhs != rhs) << std::endl;
		std::cout << std::endl;
	}

	// Int or Uint can single use.
	// can use Int to initialize the Uint, Uint convert to Int must call toUint() function.
	// operator 
	static void testTwo() {
		{
			double a = 10.8;// mwgcc 4.8.0 (no), vc6.0 (no)
			int b = a; // mwgcc 4.8.0 (no), vc6.0 (no) 
		}
		try {
			{	typedef test::Int test_type;
				test_type a(-100);
	//			test_type b(UINT_MAX); // exception.
				test_type min(INT_MIN);
				test_type max(INT_MAX);
	//			min--; // exception.
	//			max++; // exception.
	//			test_type c = max + max; // exception
				test_type d = max + a; 
	//			test_type e = a + min; // exception
				test_type f = min - a;
				++d; --d;
				f++; f--;
				test_type g = +d;
				test_type h = -f;
	//			test_type i = -min; // exception
	//			test_type j = a * d; // a == -100, d == max + -100 exception
				test_type k = a * a;
	//			test_type l = f / 0; // exception
				test_type m = f / d; 
				
				testTwo_Helper(d, f);
				d = f;
				testTwo_Helper(d, f);
			}
			{	typedef test::Uint test_type;
				test_type a(100);
	//			test_type b(-100); // exception.
				test_type min(0);
				test_type max(UINT_MAX);
	//			min--; // exception.
	//			max++; // exception.
	//			test_type c = max + max; // exception
				test_type d = max - a; 
	//			test_type e = min - a; // exception
				test_type f = a - min;
				++d; --d;
				f++; f--;
				test_type g = +d;
	//			test_type h = -f; // exception
	//			test_type i = -min; // exception
	//			test_type j = a * d; // a == 100, d == max -100 exception
				test_type k = a * a;
	//			test_type l = f / 0; // exception
				test_type m = f / d; 
				
				testTwo_Helper(d, f);
				d = f;
				testTwo_Helper(d, f);
			}
			{
				test::Int a(10);
				test::Uint b(100);
	//			test::Int c = b + a; // not ok, see variable e.
				test::Uint d = b + a;
				test::Int e = (a + d - d).toUint(); // a + b - d
	//			test::Int f = e / d;
	//			test::Uint d = a + 30; // test::Int d = a;
				test::Uint f = b; // test::Int f = b;

				testTwo_Helper(d, f);
				d = f;
				testTwo_Helper(d, f);
			}
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			throw;
		}
	}
	@endcode
*/
#ifndef Test_Suit_01_Head
#define Test_Suit_01_Head

#include <iostream>		// operator<< and operator>>
#include <limits> 		// std::numeric_limits
#include <stdexcept>	// excptions
#include "log.h" // LOG_XXX maroc.


namespace test {

// T have -, <.
template<typename T>
inline bool isless(const T& lhs, const T& rhs) {
	return lhs - std::numeric_limits<T>::epsilon() < rhs;
}

template<typename T>
inline bool isbig(const T& lhs, const T& rhs) {
	return isless(rhs, lhs);
}

template<typename T>
inline bool isequal(const T& lhs, const T& rhs) {
	return isless(lhs, rhs) == isbig(lhs, rhs); // xor(lhs < rhs, lhs > rhs);
}


// operator test. T have +, -, *, /
template<typename T>
inline bool isadd_ok(const T& lhs, const T& rhs) {	
	T ans = lhs + rhs; 
	T newlhs = ans - rhs;
	return isequal(lhs, newlhs); // this algorithm not good for int or unsigned type.
}

template<typename T>
inline bool issub_ok(const T& lhs, const T& rhs) { 
	T ans = lhs - rhs;
	T newlhs = ans + rhs;
	return isequal(lhs, newlhs); // this algorithm not good for int or unsigned type.
}

template<typename T>
inline bool ismult_ok(const T& lhs, const T& rhs) {
	T ans = lhs * rhs;
	T newlhs = rhs ? ans / rhs : lhs; // test rhs is 0, no for newlhs is lhs.
	return !rhs || isequal(lhs, newlhs); // !(rhs && (ans / rhs != lhs))
}

template<typename T>
inline bool isdiv_ok(const T& lhs, const T& rhs) { return rhs != 0;}

// specialize for int or...
template<>
inline bool isadd_ok<int>(const int& lhs, const int& rhs) {
	int ans = lhs + rhs; 
	bool t1 = (lhs < 0 && rhs < 0) || (lhs >= 0 && rhs >= 0); // is same sign;
	bool t2 = (lhs < 0 && ans >= 0) || (lhs >= 0 && ans < 0); // is ans's sign different from lhs.
	return !(t1 && t2);
}

template<>
inline bool issub_ok<int>(const int& lhs, const int& rhs) {
	int ans = lhs - rhs; 
	bool t1 = (lhs < 0 && rhs >= 0) || (lhs >= 0 && rhs < 0); // is have different sign.
	bool t2 = (lhs < 0 && ans >= 0) || (lhs >= 0 && ans < 0); // is ans's sign different from lhs.
	return !(t1 && t2);
}

// specialize for int or...
template<>
inline bool isadd_ok<unsigned int>(const unsigned int& lhs, const unsigned int& rhs) {
	unsigned int ans = lhs + rhs; 
	return ans >= lhs && ans >= rhs; // this is special for unsigned.
}

template<>
inline bool issub_ok<unsigned int>(const unsigned int& lhs, const unsigned int& rhs) {
	return lhs >= rhs; // this is special for unsigned.
}


namespace details {

template<typename T>
struct Operator {
	// one
	friend const T operator++(T& t, int) {
		T tmp(t);
		t.operator++();
		return tmp;
	}

	friend const T operator--(T& t, int) {
		T tmp(t);
		t.operator--();
		return tmp;
	}
	
	// +a
	friend const T& operator+(const T& t) {
		return t;
	}
	
	friend bool operator!(const T& t) { 
		return !t.i;
	}

	// 2
	friend const T operator+(const T& lhs, const T& rhs) {
		return T(lhs) += rhs;
	}

	friend const T operator-(const T& lhs, const T& rhs) {
		return T(lhs) -= rhs;
	}

	friend const T operator*(const T& lhs, const T& rhs) {
		return T(lhs) *= rhs;
	}

	friend const T operator/(const T& lhs, const T& rhs) {
		return T(lhs) /= rhs;
	}

	friend bool operator>(const T& lhs, const T& rhs) {
		return rhs < lhs;
	}

	friend bool operator<=(const T& lhs, const T& rhs) {
		return !(rhs < lhs);
	}

	friend bool operator>=(const T& lhs, const T& rhs) {
		return !(lhs < rhs);
	}

	friend bool operator==(const T& lhs, const T& rhs) {
		return !(lhs < rhs) && !(rhs < lhs);
	}

	friend bool operator!=(const T& lhs, const T& rhs) {
		return !(lhs == rhs);
	}
	
	friend std::ostream& operator<<(std::ostream& os, const T& t) {
		return os << t.i;
	}

	friend std::istream& operator>>(std::istream& is, const T& t) {	
		return is >> t.i;
	}
};

static inline void out_of_range(bool is, const char* extra) {
	if (is) {
		std::string str = extra;
		str += " is out of range.";
#ifdef NOT_THROW_EXCEPTION
		LOG_DEBUG(str.c_str());
#else
		throw std::out_of_range(str);
#endif
	}
}

static inline void invalid_argument(bool is, const char* extra) {
	if(is) {
		std::string str = extra;
		str += " is invalid argument.";
#ifdef NOT_THROW_EXCEPTION
		LOG_DEBUG(str.c_str());
#else
		throw std::invalid_argument(str);
#endif
		
	}
}

template<typename T>
// static 
inline void init_test_Int(T t) {
	bool t1 = t > INT_MAX;
	bool t2 = t < INT_MIN;
	out_of_range(t1 || t2, " param[in] n at Int::Int<T>(n)");
}

template<>
// static // g++(MinGW 4.8.0) dont need static, vc6.0 must same as init_test_Int();
inline void init_test_Int<unsigned int>(unsigned int t) {
	bool t1 = t > INT_MAX;
	out_of_range(t1, " param[in] n at Int::Int<T>(n)");
}

template<typename T>
static inline void init_test_Uint(T t) {
	bool t1 = t > UINT_MAX;
	bool t2 = t < 0;
	out_of_range(t1 || t2, " param[in] n at Uint::Uint<T>(n)");
}

} // namespace details

struct Int;
struct Uint;

#define CTOR_OF(name, type) name(type ii) : i(ii) { details::init_test_##name(ii);}

struct Int : public details::Operator<Int> {
	int i;
	typedef int data_type;
	typedef Int this_type;

	CTOR_OF(Int, char)
	CTOR_OF(Int, unsigned char)
	CTOR_OF(Int, short)
	CTOR_OF(Int, unsigned short)
	CTOR_OF(Int, int)
	CTOR_OF(Int, unsigned int)
	CTOR_OF(Int, long)
	CTOR_OF(Int, unsigned long)
//	CTOR_OF(Int, long long)
//	CTOR_OF(Int, unsigned long long)
	CTOR_OF(Int, float)
	CTOR_OF(Int, double)
	CTOR_OF(Int, long double)
	
	Int(const Int& ci) : i(ci.i) { details::init_test_Int(ci.i);}
	int toInt() const { return i;}
//	Int(const Uint& ui); // will case problem

/*	// will case problem
	template<typename T>
	Int(T n) : i(n) {
		bool t1 = n > INT_MAX;
		bool t2 = n < INT_MIN;
		out_of_range(t1 || t2, " param[in] n at Int::Int<T>(n)");
	}
	
	operator int () { return i;}
*/
	const this_type& operator++() {
		details::out_of_range(i == INT_MAX, " Int::operator++()");
		++i;
		return *this;
	}

	const this_type& operator--() {
		details::out_of_range(i == INT_MIN, " Int::operator++()");
		--i;
		return *this;
	}

	const this_type operator-() const {
		details::out_of_range(i == INT_MIN, " Int::operator-()"); // -INT_MIN undefine.
		return -i;
	}

	this_type& operator+=(const this_type& rhs) {
		details::out_of_range(!isadd_ok(i, rhs.i), " Int::operator+=(rhs)");
		i += rhs.i;
		return *this;
	}

	this_type& operator-=(const this_type& rhs) {
		details::out_of_range(!issub_ok(i, rhs.i), " Int::operator-=(rhs)");
		i -= rhs.i;
		return *this;
	}

	this_type& operator*=(const this_type& rhs) {
		details::out_of_range(!ismult_ok(i, rhs.i), " Int::operator*=(rhs)");
		i *= rhs.i;
		return *this;
	}

	this_type& operator/=(const this_type& rhs) {
		details::invalid_argument(!isdiv_ok(i, rhs.i), " rhs.i is 0 in Int::operator/=(rhs)");
		i /= rhs.i;
		return *this;
	}
	
	friend bool operator<(const this_type& lhs, const this_type& rhs) {
		return lhs.i < rhs.i;
	}
};


struct Uint : public details::Operator<Uint>{
	unsigned int i;
	typedef unsigned int data_type;
	typedef Uint		 this_type;
	
	CTOR_OF(Uint, char)
	CTOR_OF(Uint, unsigned char)
	CTOR_OF(Uint, short)
	CTOR_OF(Uint, unsigned short)
	CTOR_OF(Uint, int)
	CTOR_OF(Uint, unsigned int)
	CTOR_OF(Uint, long)
	CTOR_OF(Uint, unsigned long)
//	CTOR_OF(Uint, long long)
//	CTOR_OF(Uint, unsigned long long)
	CTOR_OF(Uint, float)
	CTOR_OF(Uint, double)
	CTOR_OF(Uint, long double)

	Uint(const Int& t) : i(t.i) { details::init_test_Uint(t.i);}
	Uint(const Uint& ci) : i(ci.i) { details::init_test_Uint(ci.i);}
	unsigned int toUint() const { return i;}
//	operator Int () { Int::init_test(i); return i;}

	const this_type& operator++() {
		details::out_of_range(i == UINT_MAX, " Uint::operator++()");
		++i;
		return *this;
	}

	const this_type& operator--() {
		details::out_of_range(i == 0, " Uint::operator++()");
		--i;
		return *this;
	}
	
	const this_type operator-() const {
		details::out_of_range(true, " Uint::operator-()"); 
		return 0;
	}

	this_type& operator+=(const this_type& rhs) {
		details::out_of_range(!isadd_ok(i, rhs.i), " Uint::operator+=(rhs)");
		i += rhs.i;
		return *this;
	}

	this_type& operator-=(const this_type& rhs) {
		details::out_of_range(!issub_ok(i, rhs.i), " Uint::operator-=(rhs)");
		i -= rhs.i;
		return *this;
	}

	this_type& operator*=(const this_type& rhs) {
		details::out_of_range(!ismult_ok(i, rhs.i), " Uint::operator*=(rhs)");
		i *= rhs.i;
		return *this;
	}

	this_type& operator/=(const this_type& rhs) {
		details::invalid_argument(!isdiv_ok(i, rhs.i), " rhs.i is 0 in Uint::operator/=(rhs)");
		i /= rhs.i;
		return *this;
	}

	friend bool operator<(const this_type& lhs, const this_type& rhs) {
		return lhs.i < rhs.i;
	}
};

//Int::Int(const Uint& ui) : i(ui.i) { init_test(ui.i);}

} // namespace test

namespace std {
template<>
class numeric_limits<test::Int>
 : public std::numeric_limits<int> {};

template<>
class numeric_limits<test::Uint>
 : public std::numeric_limits<unsigned int> {};
} // namespace std


#endif // Test_Suit_01_Head