#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/iter_range.hpp>


#include <string>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/filtered.hpp>
#include <pstade/locale.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("hello,iter_range!!!!");
    {
        oven::iter_range<std::string::iterator> rng(src);
        std::vector<char> expected = src|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng, expected
        ) );

        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            oven::make_iter_range(src), expected
        ) );
 
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            oven::make_iter_range(boost::begin(src), boost::end(src)), expected
        ) );

        BOOST_CHECK( oven::test_is_lightweight_proxy(rng) );
        BOOST_CHECK( oven::make_iter_range(src)[4] == 'o' );
        BOOST_CHECK( oven::make_iter_range(src)[4] = 'o' );
        BOOST_CHECK( oven::make_iter_range(src)[4] == 'o' );
    }
    {
        oven::iter_range<std::string::iterator> rng1(src);
        oven::iter_range<std::string::iterator> rng2(src);
        oven::iter_range<std::string::iterator> rng3(rng1);
        oven::iter_range<std::string::iterator> rng4(rng3);
        oven::iter_range<std::string::iterator> rng5;
        BOOST_CHECK( rng1 == rng4 );
        BOOST_CHECK( !(rng1 != rng4 ) );
        rng2 = src;
        BOOST_CHECK( rng1 == rng2 );
        BOOST_CHECK( !(rng1 != rng2 ) );
    }
    {
        iter_range<std::string::iterator> rng1(src);
        iter_range<std::string::const_iterator> rng2 = rng1; // implicit conversion
        BOOST_CHECK( equals(rng1, rng2) );
    }
    {
        boost::iterator_range<std::string::iterator> rng1(src);
        iter_range<std::string::const_iterator> rng2 = rng1; // implicit conversion
        BOOST_CHECK( equals(rng1, rng2) );
    }
    {
        std::pair<std::string::iterator, std::string::iterator> rng1(src.begin(), src.end());
        iter_range<std::string::const_iterator> rng2 = rng1; // implicit conversion
        BOOST_CHECK( equals(rng1, rng2) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
