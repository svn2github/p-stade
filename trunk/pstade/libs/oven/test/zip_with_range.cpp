#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/zip_with_range.hpp>


#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/algorithms.hpp>


struct plus
{
    typedef int result_type;

    int operator()(int x, int y) const
    {
        return x + y;
    }
};


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
        int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
        int ans[] = { 1, 7, 3, 5,11,13, 9 };

        BOOST_CHECK( oven::equals(
            xs|zipped_with(ys, ::plus()),
            ans
        ) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
