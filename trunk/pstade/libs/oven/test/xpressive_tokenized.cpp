#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/xpressive_tokenized.hpp>


#include <string>
#include <vector>
#include <boost/xpressive/xpressive.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/concatenated.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string input("This is his face");
        boost::xpressive::sregex re = +boost::xpressive::_w; // a word

        bool f = false;
        if (f) {
            input|xpressive_tokenized(re);
            input|xpressive_tokenized(re, -1);
            input|xpressive_tokenized(re, std::vector<int>(), boost::xpressive::regex_constants::match_default);
        }

        BOOST_CHECK( oven::equals(input|xpressive_tokenized(re)|concatenated, std::string("Thisishisface") ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}