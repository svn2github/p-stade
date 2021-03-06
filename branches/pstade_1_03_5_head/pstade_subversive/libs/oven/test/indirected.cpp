#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/indirected.hpp>


#include <iterator>
#include <string>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/algorithm.hpp>
#include <pstade/oven/transformed.hpp>


struct A
{
    void call();
};


int *to_rvalue_pointer(int& x)
{
    return &x;
}


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        int ans[] = { 2,4,5,1,3 };
        int *rng[] = { &ans[0], &ans[1], &ans[2], &ans[3], &ans[4] };

        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|indirected,
            expected
        ) );
    }
    {
        // can resurrect lvalue-ness.
        int rng[] = { 2,4,5,1,3,9,7,10,0 };

        std::vector<int> expected = rng|copied;
        BOOST_CHECK( oven::test_RandomAccess_Readable_Writable(
            rng|transformed(&to_rvalue_pointer)|indirected,
            expected
        ) );
    }

    char characters[] = "abcdefg";
    const int N = sizeof(characters)/sizeof(char) - 1; // -1 since characters has a null char
    char* pointers_to_chars[N];                        // at the end.
    for (int i = 0; i < N; ++i)
        pointers_to_chars[i] = &characters[i];

    char ans[] = "abcdefg";
    {
        BOOST_CHECK((
            oven::equal( oven::make_indirected(pointers_to_chars), ans)
        ));
    }

    {
        BOOST_CHECK((
            oven::equal(
                pointers_to_chars |
                    oven::indirected,
                ans
            )
        ));
    }

    /*
    {
        std::vector<A*> vec;
        typedef indirect_range< std::vector<A*> > rng_t;
        rng_t rng(vec);
        boost::range_result_iterator< rng_t >::type it = boost::begin(rng);
        (*it).call();
        it->call();
    }
    */
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
