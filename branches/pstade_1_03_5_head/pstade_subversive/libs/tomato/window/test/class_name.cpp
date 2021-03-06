#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>
#include <pstade/apple/wtl/app.hpp>
WTL::CAppModule _Module;


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/class_name.hpp>


#include <pstade/oven/wtl.hpp>
#include <pstade/oven/copy_range.hpp>

#include <iostream>
#include <pstade/apple/atl/str.hpp>
#include <pstade/apple/atl/config.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/misc.hpp>
#include <pstade/apple/wtl/app.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/tstream.hpp>


void test()
{
    using namespace pstade;
    using namespace tomato;

    HWND hWnd = ::GetForegroundWindow();

#if (PSTADE_APPLE_ATL_VER >= 0x0700)
    {
        ATL::CString str = tomato::class_name(hWnd)|oven::copied;
        tcout << tomato::c_str(str) << std::endl;
    }
#endif

    {
        WTL::CString str = tomato::class_name(hWnd)|oven::copied;
        tcout << tomato::c_str(str) << std::endl;
    }

    {
        tomato::class_name name(hWnd);
        WTL::CString str = name|oven::copied;
        tcout << tomato::c_str(str) << std::endl;
    }

    {
        tomato::class_name const name(hWnd);
        WTL::CString str = name|oven::copied;
        tcout << tomato::c_str(str) << std::endl;
    }

    {
        tomato::class_name cn(hWnd);
        // *boost::begin(cn) = _T('a'); // error
    }
}


int test_main(int, char *[])
{
    ::test();
    return 0;
}
