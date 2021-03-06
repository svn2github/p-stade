

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/nest.hpp>
#include "./egg_test.hpp"


#include <boost/egg/lazy.hpp>
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/functional.hpp> // plus


#include "./using_egg.hpp"
namespace bll = boost::lambda;


struct T_my_apply
{
    typedef int result_type;

    template<class F>
    int operator()(F f, int n) const
    {
        return f(n);
    }
};

T_my_apply const my_apply = {};

result_of_lazy<T_my_apply>::type const my_Apply = BOOST_EGG_LAZY({});


int plus_2(int i) { return i + 2; }
int mult_3(int i) { return i * 3; }
int minus_5(int i) { return i - 5; }


void egg_test()
{
    result_of_<T_lazy(T_plus const&)>::type Plus = lazy(plus);

    using bll::_1;
    using bll::_2;

    int a = 3, b = 5;

    // \x -> plus(7, x)
    BOOST_CHECK( Plus(7, _1)
        (a) == plus(7, a) );

    // \(x,y) -> plus(plus(x), y)
    BOOST_CHECK( Plus(Plus(4, _1), _2)
        (a, b) == plus(plus(4, a), b) );

    // \x -> (\y -> plus(x, y))
    BOOST_CHECK( lazy(bll_bind)(plus, _1, bll::protect(_1))
        (a)(b) == plus(a, b) );

    // complicated
    // \x -> my_apply(\y -> plus(x, y), plus(x, 3))
    BOOST_CHECK( my_Apply(lazy(bll_bind)(plus, _1, bll::protect(_1)), Plus(_1, 3))
        (a) == plus(a, a+3) );


    typedef result_of_lazy<T_bll_bind>::type T_Bind;
    T_Bind Bind;

    BOOST_CHECK( my_Apply(Bind(plus, _1, bll::protect(_1)), Plus(_1, 3))
        (a) == plus(a, a+3) );

    typedef result_of_lazy<T_plus, T_Bind>::type T_PLus;
    T_PLus PLus;

    BOOST_CHECK( my_Apply(PLus(_1, bll::protect(_1)), Plus(_1, 3))
        (a) == plus(a, a+3) );

    // using `nest` and `nest`
    BOOST_CHECK( nest1(my_apply)(nest2(plus)(_0_(_1), _1_(_1)), nest1(plus)(_0_(_1), 3))
        (a) == plus(a, a+3) );

    // function composition
    BOOST_CHECK( nest1(&plus_2)(nest1(&mult_3)(nest1(&minus_5)(_1)))(a) == plus_2(mult_3(minus_5(a))) );
}
