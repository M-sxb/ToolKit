// this file is under no license.
/** @file Newer.h
	@brief class Newer.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add class Newer.

	<b>10-14-2015</b> 

	- add new count log output.
*/


#ifndef Newer_Head
#define Newer_Head


#include <sstream>
#include <string>
#include "log.h"


namespace {

template<class CharT> 
std::basic_string<CharT> TrackNewCount_Str(int type, long count, void* ptr, size_t size) {
	std::basic_ostringstream<CharT> oss;
	switch(type) {
	case 0:
		oss << "  Alloc[new]\t\t(" << count << ") 0X" << ptr << " - " << size << " Bytes.";
		break;
	case 1:
		oss << "Dealloc[delete]\t\t(" << count << ") 0X" << ptr << ".";
		break;
	case 2:
		oss << "  Alloc[new[]]\t\t(" << count << ") 0X" << ptr << " - " << size << " Bytes.";
		break;
	case 3:
		oss << "Dealloc[delete[]]\t(" << count << ") 0X" << ptr << ".";
		break;
	case 4:
		oss << "  Alloc[allocate]\t(" << count << ") 0X" << ptr << " - " << size << " Bytes.";
		break;
	case 5:
		oss << "Dealloc[deallocate]\t(" << count << ") 0X" << ptr << ".";
		break;
	default:
		oss << "Unknown new count. type:" << type 
			<< " count:" << count << " ptr:" << ptr << " size:" << size;
	}
	return oss.str();
}

template<> 
std::basic_string<wchar_t> TrackNewCount_Str<wchar_t>(int type, long count, void* ptr, size_t size) {
	std::basic_ostringstream<wchar_t> oss;
	switch(type) {
	case 0:
		oss << L"  Alloc[new]\t\t(" << count << ") 0X" << ptr << L" - " << size << L" Bytes.";
		break;
	case 1:
		oss << L"Dealloc[delete]\t\t(" << count << L") 0X" << ptr << L".";
		break;
	case 2:
		oss << L"  Alloc[new[]]\t\t(" << count << ") 0X" << ptr << L" - " << size << L" Bytes.";
		break;
	case 3:
		oss << L"Dealloc[delete[]]\t(" << count << L") 0X" << ptr << L".";
		break;
	case 4:
		oss << L"  Alloc[allocate]\t(" << count << L") 0X" << ptr << L" - " << size << L" Bytes.";
		break;
	case 5:
		oss << L"Dealloc[deallocate]\t(" << count << L") 0X" << ptr << L".";
		break;
	default:
		oss << L"Unknown new count. type:" << type 
			<< L" count:" << count << L" ptr:" << ptr << L" size:" << size;
	}
	return oss.str();
}

/**
	@param[in] type 
	type == 0 new, 
	type == 1 delete
	type == 2 new[]
	type == 3 delete[]
	type == 4 allocate
	type == 5 deallocate
*/ 
void TrackNewCount(int type, void* ptr, size_t size = 0) {
	typedef defLog::type::InCharT CharT;
	static long count = 0;

	if(type%2 == 0) ++count;
	else --count;
	std::basic_string<CharT> str = TrackNewCount_Str<CharT>(type, count, ptr, size);
	LOG_INFO(str.c_str());	
}

} // namespace

/** Newer is a test class for memory leck.
	@todo 
	- add extral string using to specily who's operation.
	- a new name needed like \c Allocater ?
	- have memory control method, like \c allocate which defined in \c std ?
*/
struct Newer {
	virtual ~Newer() {} 
	static void* operator new(size_t size) {
		void* ptr = ::operator new(size);
		TrackNewCount(0, ptr, size);
		return ptr;
	}

	static void operator delete(void* ptr) {
		TrackNewCount(1, ptr);
		::operator delete(ptr);
	}
	
//	static void operator delete(void* ptr, size_t size) {
//		::operator delete(ptr);
//	}

	static void* operator new[](size_t size) {
		void* ptr = ::operator new(size);
		TrackNewCount(2, ptr, size);
		return ptr;
	}

    //! @bug for gcc delete[] will fail, 
	static void operator delete[](void* ptr) {
		TrackNewCount(3, ptr);
		::operator delete(ptr);
	}

	template<typename T>
	inline static T* allocate(size_t n, T*) throw() {
		T* ptr = 0;
		try {
			ptr = static_cast<T*>(::operator new( n * sizeof(T)));
		} catch(...) {
			ptr = 0;
		}
		
		TrackNewCount(4, ptr, n * sizeof(T));
		return ptr;
	}
	
	template<typename T>
	inline static void deallocate(T* ptr) throw() {
		TrackNewCount(5, ptr);
		::operator delete( ptr);
	}
};


#endif // Newer_Head
