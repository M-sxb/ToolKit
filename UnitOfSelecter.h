// this file is under no license.
/** @file UnitOfSelecter.h
	@brief UnitOfSelecter.h contains template class using to 
	@date 
	@version
	@authors
	@attention This file is still under modification. Support template specialize needed.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add class RangeSelecter<int, int ,int>, 
	class UnitOf_Imp<int, bool, class>, class UnitOfSelecter<int, class>.
	- add new version of class UnitOfSelecter<int, class> which do not using UnitOf_Imp.
*/


#ifndef UnitOfSelecter_Head
#define UnitOfSelecter_Head


/** selecte unit form template argument UnitOf.
	@example see at \em UnitOfTime for form of UnitOf.
*/
template<int uof, class UnitOf>
struct UnitOfSelecter {
	static const char* struof;
};
template<int u, class UnitOf>
const char* UnitOfSelecter<u, UnitOf>::struof = 
							UnitOf::uof[u > UnitOf::MAX_UNITS - 1 ? UnitOf::DEFAULT_UNITS : u];													



#endif // UnitOfSelecter_Head
