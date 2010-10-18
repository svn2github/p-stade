#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame, Akira Takahashi 2005-2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/zipped_with_index.hpp>
#include <boost/test/minimal.hpp>
#include "./detail/v1_tests.hpp"


#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"


#include <boost/tuple/tuple_comparison.hpp> // DON'T FORGET for Readable test


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string rng("0123");

        typedef boost::tuple<char, std::size_t> tt;
        std::vector<tt> expected;
        expected.push_back(tt('0', 0));
        expected.push_back(tt('1', 1));
        expected.push_back(tt('2', 2));
        expected.push_back(tt('3', 3));

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|zipped_with_index,
            expected
        ) );
    }
    {
        std::string src("0123456");
        std::string ans("0123556");

        BOOST_FOREACH (
            PSTADE_UNPARENTHESIZE((boost::tuple<char&, std::size_t>)) t,
            src|zipped_with_index
        ) {
            char& ch = boost::get<0>(t);
            if (ch == '4')
                ch = '5';
        }
    
        BOOST_CHECK(( oven::equals(src, ans) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}

