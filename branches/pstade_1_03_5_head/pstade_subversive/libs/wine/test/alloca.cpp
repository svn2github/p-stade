#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/alloca.hpp>


void test()
{
    using namespace pstade;

    PSTADE_ALLOCA(int *, p, 16);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
