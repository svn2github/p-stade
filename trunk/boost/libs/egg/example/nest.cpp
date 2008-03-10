

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include <functional> // plus
#include <boost/egg/apply.hpp>


#include "./using_bll.hpp"
#include "./egg_example.hpp"


int foo(int i, int j, int k, int m)
{
    return i + j - k + m;
}


//[code_example_nest
void egg_example()
{
    using bll::_1;
    using bll::_2;
    std::plus<int> plus;
    std::minus<int> minus;

    int i6 = 6, i1 = 1, i3 = 3, i9 = 9;

// Lv: 0     1      2          3
    // \x -> (\y -> (\(z,w) -> foo(y,w,z,x))))
    BOOST_CHECK( nest3(foo)(nest1(_1), nest2(_2), nest2(_1), nest0(_1)) /*< `nest0` does nothing, meaning that `nest0(_1)` behaves as `_1`. >*/
        (i3)(i6)(i1,i9) == foo(6,9,1,3) );

    // \x -> apply(\y -> minus(x,y), plus(x,3))
    BOOST_CHECK( nest1(apply)(nest2(minus)(nest0(_1), nest1(_1)), nest1(plus)(nest0(_1), 3)) /*< `nest1(apply)` has the same semantics as `lazy(apply)`. >*/
        (i9) == minus(9, plus(9,3))  );
}
//]