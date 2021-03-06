#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/counter.hpp>


#include <string>
#include <boost/range.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./core.hpp"
#include <pstade/oven/utf8_encoder.hpp>
#include <pstade/oven/adapted_to_base.hpp>
#include <pstade/oven/uniqued.hpp>
#include <pstade/unused.hpp>


namespace oven = pstade::oven;
using namespace oven;


void test()
{
    {
        int const rng[] = { 0,0,1,1,2,3,3,3,4,4,4,4,4,5,5 };
        int i = oven::copy(rng|uniqued, oven::counter(0))|to_base;
        BOOST_CHECK( i == 6 );

        BOOST_CHECK( 7 == oven::adapted_to<int>(oven::unique_copy(rng, oven::counter(1))) );
        BOOST_CHECK( 7 == oven::adapted_to<int>( oven::adapted_to<int>(oven::unique_copy(rng, oven::counter(1))) ) );

#if 0 // result_of seems useless...

        boost::result_of<op_counter(int)>::type k = oven::unique_copy(rng, oven::counter(1));
        BOOST_CHECK( k.function().incrementable() == 7 );
#endif

#if 0 // Lovely VC++7.1 fails to link, funny!
        int i = oven::unique_copy(rng, oven::counter(0))|to_base|to_base;
        BOOST_CHECK( i == 6 );
#endif

    }
    {
        std::wstring rng(L"aabbbcccdddeffg");
        int i = oven::adapted_to<int>(oven::unique_copy(rng, oven::utf8_encoder(oven::counter(0))));
        int j = oven::unique_copy(rng, oven::utf8_encoder(oven::counter(0)))|to_base;
        BOOST_CHECK( i == j && i == 7 );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
