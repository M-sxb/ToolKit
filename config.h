// this file is under no license.
/** @file config.h
	@brief config.h contains marco that using in the toolkit.
	@date 
	@version
	@authors
	@attention This file is still under modification.
	@details 

	<b>10-12-2015</b> 

	- builded this file.
	- add macro SUPPORT_TEMPLATE_SPECIALIZE

    <b>10-13-2015</b> 

   	- add macro WORK_WITH_MFC
   	- add macro DEBUG_MODE and DEBUG_MODE_OFF, be aware that in MSVC will automatically define 
   	those macro.
   	- test example:
   	@code{.h}
   	#ifndef SUPPORT_TEMPLATE_SPECIALIZE
	#pragma message("not SUPPORT_TEMPLATE_SPECIALIZE")
	#else
	#pragma message("SUPPORT_TEMPLATE_SPECIALIZE")
	#endif

	#ifndef WORK_WITH_MFC
	#pragma message("not WORK_WITH_MFC")
	#else
	#pragma message("WORK_WITH_MFC")
	#endif

	#ifndef DEBUG_MODE
	#pragma message("not DEBUG_MODE")
	#else
	#pragma message("DEBUG_MODE")
	#endif
   	@endcode
*/


#ifndef Config_Head
#define Config_Head

#include "platform.h"
#include "user_config.h"


#if defined(_MSC_VER) 
#   if _MSC_VER >= 1300 // VC 6.0 seems not support template specialize
#		define SUPPORT_TEMPLATE_SPECIALIZE 
#	endif
//! @todo add a warning control. like SHOW_ALL_WAENING in user_config.h
#	if _MSC_VER == 1200 // disable VC6.0 warning 4786.
#		pragma warning(disable: 4786)
#	endif
#endif // _MSC_VER

#ifdef _MFC_VER
#	define WORK_WITH_MFC
#endif // _MFC_VER

// a copy of `Ogre` Source file `OgrePlatform.h` ver 1.8.0 at line 00171.
// Win32 compilers use _DEBUG for specifying debug builds.
// for MinGW, we set DEBUG
#if defined(_DEBUG) || defined(DEBUG)
#	define DEBUG_MODE
#else
#	define DEBUG_MODE_OFF
#endif // 

#endif // Config_Head