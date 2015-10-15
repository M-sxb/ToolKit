// this file is under no license.
/** @file SmartPtr.h
	@brief class SmartPtr.
	@date 10-7-2015 
	@version
	@authors
	@attention This file is still under modification.
	@details 
	
	<b>10-12-2015</b> 

	- builded this file.
	- modefiy old file to more formatable one.

	<b>10-14-2015</b> 

	- SmartPtrCount now inhreited from Newer
*/


#ifndef SmartPtr_Head
#define SmartPtr_Head


#include <cassert> // assert
#include "Newer.h" // class Newer


//! default deleter
template<class T>
void defaultDeleter(T* p) {
	if(p) delete p;
}

//! none deleter
template<class T>
void noneDeleter(T* p) {}


/** smart pointer.
	@attetion this class is still under modification. 
	@todo 
	- using Deleter functor to repalce the delete function ptr.
	<b>9-18-2015 <\b> 

	- change SmartPtrData to SmartPtrCount,
	- add deleter fun. move old private function in SmartPtr to SmartPtrCount.

	<10-7-2015>

	- add getDel for SmartPtrCount.
*/
template<class T>
class SmartPtr {

	template<class Type>
	struct SmartPtrCount : public Newer {
		
		typedef void(*Del)(Type*);
		typedef Type* PtrT;
		
		unsigned int count;
		PtrT ptr;
		Del del;

		SmartPtrCount(PtrT p, Del deleter) 
			: count(1), ptr(p), del(deleter) {}

		unsigned int addCount() {
			return ++count;
		}
		unsigned int releaseCount() {
			return --count;
		}
		bool isPtrNull() const {
			if( ptr) return false;
			return true;
		}
		void deletePtr() {
			if( !del) return ;
			if( ptr) del(ptr);
			ptr = 0;
		}

		PtrT get() const { return ptr;}
		
		void reset(PtrT p) {
			if(ptr) deletePtr();
			ptr = p;
		}

		Del getDel() const { return del;}
	};
	
	typedef SmartPtrCount<T> SPData;
	typedef typename SmartPtrCount<T>::Del Del;

	SPData* ptr_;
	
public:
	explicit SmartPtr(T* ptr) {
		ptr_ = new SPData(ptr, defaultDeleter<T>);
	}

	SmartPtr(T* ptr, Del del) {
		ptr_ = new SPData(ptr, del);
	}
	
	virtual ~SmartPtr() {
		if( ptr_->releaseCount() == 0) {
			ptr_->deletePtr();
			delete ptr_;
		}
		ptr_ = 0;
	}

	SmartPtr(const SmartPtr& sp) {
		sp.ptr_->addCount();
		ptr_ = sp.ptr_;
	}

	SmartPtr& operator=(const SmartPtr& sp) {
		if( ptr_->releaseCount() == 0) {
			ptr_->deletePtr();
			delete ptr_;
			ptr_ = 0;
		}
		sp.ptr_->addCount();
		ptr_ = sp.ptr_;
		return *this;
	}
	
	T* operator->() {
		assert(!ptr_->isPtrNull());
		return get();
	}
	const T* operator->() const {
		assert(!ptr_->isPtrNull());
		return get();
	}

	T& operator*() {
		return *((*this).operator->());
	}
	const T& operator*() const {
		return *((*this).operator->());
	}

	void reset(T* ptr) {
		if( ptr_->releaseCount() == 0) {
			ptr_->reset(ptr);
			ptr_->addCount();
			return ;
		}

		ptr_ = new SPData(ptr, ptr_->getDel());
	}

	T* get() const {
		return ptr_->get();
	}
	
	bool operator!() const {
		return ptr_->isPtrNull();
	}	
};

template<class T>
inline bool operator==(const SmartPtr<T>& lhs, const SmartPtr<T>& rhs) {
	return lhs.get() == rhs.get();
}

//! using this function instand of sp.get();
template<class T>
inline T* getPtr(const SmartPtr<T>& sp) {
	return sp.get();
}

//! using this function instand of sp.reset();
template<class T>
inline void resetPtr(SmartPtr<T>& sp, T* nptr = 0) {
	sp.reset(nptr);
}


#endif // SmartPtr_Head