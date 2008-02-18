

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/free.hpp>
#include "../test/egg_test.hpp"


namespace egg = boost::egg;
using namespace egg;

// See also 17.4.4.4.



//[code_freed_prisoner
struct cage
{
    int prisoner;
};

result_of_free<int (cage::*)>::type const
    freed_prisoner = BOOST_EGG_FREE(&cage::prisoner);

void test_prisoner()
{
    cage c = {777};
    BOOST_CHECK(freed_prisoner(c) == 777);
}
//]

void egg_test()
{
    ::test_prisoner();
}
