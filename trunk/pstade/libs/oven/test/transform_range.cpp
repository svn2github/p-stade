#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/transform_range.hpp>


#include <boost/utility/result_of.hpp>
#include <iterator>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <functional>
#include <pstade/value.hpp>
#include <pstade/functional.hpp>
#include <pstade/forward.hpp>


struct multiply2 :
    std::unary_function<int, int>
{
    int operator()(int x) const { return x*2; }
};


struct div2 :
    std::unary_function<int, int>
{
    int operator()(int x) const { return x/2; }
};


int div2_(int x) { return x/2; }


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    int src[] = { 1, 2, 3, 4, 5 };
    int ans1[] = { 2, 4, 6, 8, 10 };

    {
        int rng[] = {1,2,3,4,5};
        int ans[] = {2,4,6,8,10};
        std::vector<char> expected = ans|copied;

        BOOST_CHECK( oven::test_RandomAccess_Readable(
            rng|transformed(::multiply2()),
            expected
        ) );
    }
    {
        BOOST_CHECK((
            oven::equal( oven::make_transform_range(src, multiply2()), ans1)
        ));
    }

    {
        bool ok =
            oven::equal(
                src
                    | oven::transformed(multiply2())
                    | oven::transformed(div2())
                    | oven::transformed(multiply2())
                    | oven::transformed(&div2_)
                , src
            );
        
        BOOST_CHECK(ok);
    }
    {
        std::string str;
        str |
            transformed(pstade::value) |
            // transformed(pstade::identity); // dangling!
            transformed(pstade::forward<char>(pstade::identity));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
