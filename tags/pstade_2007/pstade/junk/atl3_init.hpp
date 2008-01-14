#ifndef PSTADE_TOMATO_ATL3_INIT_HPP
#define PSTADE_TOMATO_ATL3_INIT_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/config.hpp> // ATL_VER


#if (PSTADE_APPLE_ATL_VER < 0x0700)


    #if defined(__ATLWIN_H__)
        #error <atlwin.h> shall not be included before.
    #endif


    #pragma conform(forScope, off)
    #include <pstade/apple/atl/win.hpp>
    #pragma conform(forScope, on)
    

    #include <pstade/apple/sdk/windows.hpp>

    namespace ATL {

        inline void * __stdcall __AllocStdCallThunk()
	    {
		    return ::HeapAlloc(::GetProcessHeap(), 0, sizeof(_stdcallthunk));
	    }

	    inline void __stdcall __FreeStdCallThunk(void *p)
	    {
		    ::HeapFree(::GetProcessHeap(), 0, p);
	    }

    }

    #pragma comment(linker, "/NODEFAULTLIB:atlthunk.lib")


#endif // (PSTADE_APPLE_ATL_VER < 0x0700)


#endif
