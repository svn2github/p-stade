#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/pointed.hpp>


#include <cstring>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/functional.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/taken_while.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::vector<int> vec;
        BOOST_CHECK(( boost::empty(vec|pointed) ));
    }
    {
        std::string const src("hello, pointer_range");
        std::vector<char> vec;
        vec.resize(oven::distance(src) + 1);
        std::strcpy(vec|pointed|begins, src.c_str());
        BOOST_CHECK(( oven::equals(vec|taken_while(pstade::not_(pstade::equal_to_0)), src) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}