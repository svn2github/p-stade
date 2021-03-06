

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/compose.hpp>
#include "./egg_test.hpp"


#include <string>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/to_value.hpp>


std::string g_str("x");


struct bar_fun
{
    typedef std::string result_type;

    std::string operator()(char) const
    {
        return "x";
    }
};


// nullary check
int make_zero()
{
    return 0;
}

int increment(int i)
{
    return i + 1;
}


struct A { };
struct B { };
A get_A() { return A(); }
B get_B() { return B(); }


using namespace boost::egg;

/*
BOOST_MPL_ASSERT((
    boost::is_same<
        std::string,
        boost::egg::result_of_<
            boost::egg::result_of_<
                T_compose(T_value const, bar_fun)
            >::type
            (char)
        >::type
    >
));
*/


template<class F>
void nullary_result_of_check(F )
{
    BOOST_MPL_ASSERT((boost::is_same<
        typename boost::egg::result_of_<F()>::type,
        int
    >));
}



void egg_test()
{
    {
        BOOST_CHECK( compose(boost::egg::to_value, ::bar_fun())('c') == std::string("x") );
    }
    {
        // make_zero is known to be nullary and composable to increment.
        BOOST_CHECK(( X_compose<use_nullary_result>()(&::increment, &::make_zero)() == 1 ));
        ::nullary_result_of_check( X_compose<use_nullary_result>()(&::increment, &::make_zero) );
    }
    {
        // specify nullary result type explicity.
        BOOST_CHECK(( X_compose<int>()(&::increment, &::make_zero)() == 1 ));
        ::nullary_result_of_check( X_compose<int>()(&::increment, &::make_zero) );
    }
    {
        // well-formed even if non-composable.
        compose(&::get_A, &::get_B);
        X_compose<int>()(&::get_A, &::get_B);
    }
}
