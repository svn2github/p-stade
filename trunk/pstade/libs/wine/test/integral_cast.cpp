#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>


#include <boost/utility/result_of.hpp>


void test()
{
    using namespace pstade;

    unsigned int ui = 0;
    signed int i = 0;

    ui = pstade::op_integral_cast<signed int>()(i);
    ui = pstade::integral_cast<signed int>(i);

    ui = i|to_integer;
}


void test_()
{
    using namespace pstade;

    try {
        boost::result_of<op_integral_cast<short>(long)>::type
            s = pstade::integral_cast<short>(70000L);
    }
    catch (boost::bad_numeric_cast)
    {
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
