#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/writer.hpp>


#include <sstream>
#include <string>
#include <boost/range.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./core.hpp"
#include <pstade/oven/adapted_to_base.hpp>
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/is_same.hpp>


namespace oven = pstade::oven;
using namespace oven;


std::stringstream g_ss;


void test()
{
    std::string const src("abcdefg");

    {
        g_ss.str("");
        std::stringstream& ss = oven::adapted_to<std::stringstream&>( copy(src, writer(g_ss)) );
        BOOST_CHECK( equals(g_ss.str(), src) );
        BOOST_CHECK( pstade::is_same(ss, g_ss) );
    }
    {
        g_ss.str("");
        std::stringstream& ss = oven::adapted_to<std::stringstream&>( copy(src, writer(g_ss, ",")) );
        BOOST_CHECK( equals(g_ss.str(), std::string("a,b,c,d,e,f,g")) );
        BOOST_CHECK( pstade::is_same(ss, g_ss) );
    }
#if 0 // seems not to be able to support reference type as 'to_base' target.
    {
        std::wstring rng(L"aabbbcccdddeffg");
        std::stringstream& ss = oven::unique_copy(rng, utf8_encoder(writer(g_ss)))|to_base;
        BOOST_CHECK( pstade::is_same(ss, g_ss) );
    }
#endif
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
