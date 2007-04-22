#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/memoized.hpp>


#include <string>
#include <iostream>
#include <sstream>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/copied_out.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/stream_input.hpp>
#include <pstade/oven/io.hpp>
#include <pstade/oven/taken.hpp>


#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;
    namespace bll = boost::lambda;

#if 0
    {
        std::string ans("18284610528192");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            oven::stream_input<char>(ss)|memoized,
            expected
        ) );
    }
    {
        int const src[] = { 1,2,5,3,6,8,6,1 };
        memo_table tb;

        int const ans[] = { 1,2,5,3,6 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            src|memoized(tb)|taken(5),
            expected
        ) );
    }
#endif
    {
        std::string ans("18284610528192");
        memo_table tb;

        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ans|memoized(tb),
            expected
        ) );
    }
    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(regular(bll::_1 != 'x')) |
                    memoized |
                    copied_out(std::back_inserter(s1)) |
                    filtered(regular(bll::_1 != 'a')) |
                    memoized |
                    copied_out(std::back_inserter(s2))
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }
}

