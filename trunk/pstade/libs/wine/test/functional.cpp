#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/functional.hpp>


#include <string>


std::string add_str(std::string left, std::string right)
{
    return left + right;
}


void test()
{
    BOOST_CHECK( pstade::always(3)() == 3 );

    BOOST_CHECK(
        pstade::flip(&::add_str)("def", "abc") ==
            ::add_str("abc", "def")
    );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}