#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/match_range.hpp>


#include <string>
#include <vector>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        boost::regex re("\\s+");
        bool f = false;
        if (f) {
            std::string("This is a string of tokens.")|matched(re);
            std::string("This is a string of tokens.")|matched(re, boost::regex_constants::match_default);
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
