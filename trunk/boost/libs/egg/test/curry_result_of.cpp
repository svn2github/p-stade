#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/curry.hpp>
#include <boost/egg/pstade/minimal_test.hpp>


#include <boost/egg/pstade/result_of.hpp>
#include <boost/egg/const.hpp>


namespace egg = pstade::egg;
using namespace egg;
using pstade::result_of;


struct foo_
{
    typedef int result_type;

    int operator()(int i, int j, int k) const
    {
        return i + j + k;
    }
};

typedef result_of_curry3<foo_>::type T_foo;
BOOST_EGG_CONST((T_foo), foo) = BOOST_EGG_CURRY3({});


void pstade_minimal_test()
{
    {
        typedef result_of<T_foo(int)>::type T_foo1;
        T_foo1 const foo1 = foo(1);
        typedef result_of<T_foo1(int)>::type T_foo2;
        T_foo2 const foo2 = foo1(2);

        BOOST_CHECK( foo2(3) == 1+2+3 );
    }
}
