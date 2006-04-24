#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/tomato/window/window_text.hpp>


#include <pstade/garlic/back_inserter.hpp>
#include <pstade/tomato/garlic/customization.hpp>


#include <iostream>
#include <iterator>
#include <string>
#include <boost/microsoft/atl/str.hpp>
#include <boost/microsoft/atl/config.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/misc.hpp>
#include <boost/microsoft/wtl/app.hpp>
#include <boost/microsoft/atl/range.hpp>
#include <boost/microsoft/wtl/range.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/diet/reset_ostream.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/tomato/tstring.hpp>


WTL::CAppModule _Module;


void test()
{
    using namespace pstade;

    HWND hWnd = ::GetForegroundWindow();

#if (BOOST_MICROSOFT_ATL_VER >= 0x0700)
    {
        ATL::CString str;
        oven::copy(tomato::window_text(hWnd), garlic::back_inserter(str));
        std::cout << str << std::endl;
    }
#endif

    {
        WTL::CString str;
        oven::copy(tomato::window_text(hWnd), garlic::back_inserter(str));
        std::cout << str << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        std::basic_string<TCHAR> str;
        std::copy(boost::begin(text), boost::end(text), std::back_inserter(str));
        std::cout << str << std::endl;
    }

    {
        tomato::window_text text(hWnd);
        boost::to_upper(text);
        std::cout << text.c_str() << std::endl;
    }

    {
        typedef std::basic_string<TCHAR> tstring;
        // oven::sequenceは昨日のテクニックをboost::copy_rangeに適用したもの
        tstring str = oven::sequence(tomato::window_text(hWnd));
        std::cout << str << std::endl;
    }

    {
        std::cout << tomato::window_text(hWnd).c_str() << std::endl;
    }
}


int test_main(int, char *[])
{
    pstade::diet::reset_ostream(std::cout);
    ::test();
    return 0;
}
