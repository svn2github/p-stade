#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/reading.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include "./core.hpp"
#include <pstade/oven/copy_range.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{

    {
        std::string ans("hello,istream_range!");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::reading<char>(ss),
            expected
        ) );
    }
    {
        std::string ans("hello,istream_range!");
        std::stringstream ss;
        ss << ans;
        std::string result = oven::reading<char>(ss)|copied;
        BOOST_CHECK(( oven::equals(result, ans) ));
    }
}


void test_buf()
{
    std::string answer("hello,istreambuf_range!");

    {
        std::stringstream ss;
        ss << answer;
        std::vector<char> expected = answer|copied;

        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::readingbuf(ss),
            expected
        ) );
    }

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::readingbuf(ss)|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }

    {
        std::stringstream ss;
        ss << answer;
        std::string result = oven::readingbuf(ss.rdbuf())|copied;
        BOOST_CHECK( oven::equals(result, answer) );
    }
}


void test_line()
{
    {
        std::string src("hello\nistream\nrange\n!");
        std::stringstream ss;
        ss << src;
        std::vector<std::string> expected; {
            expected.push_back("hello");
            expected.push_back("istream");
            expected.push_back("range");
            expected.push_back("!");
        }
        BOOST_CHECK( oven::test_SinglePass_Readable(
            oven::line_reading(ss),
            expected
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    ::test_buf();
    ::test_line();
    return 0;
}
