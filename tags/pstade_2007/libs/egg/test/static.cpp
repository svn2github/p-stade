#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/static.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/indirect.hpp>
#include <pstade/egg/construct.hpp>


namespace egg = pstade::egg;
using namespace egg;



typedef static_< X_construct<int> >::type T_construct_int;
T_construct_int const construct_int = PSTADE_EGG_STATIC(X_construct<int>);


//typedef result_of_indirect<static_< X_construct<int> >::type const *>::type T_construct_int;
//T_construct_int const construct_int = PSTADE_EGG_INDIRECT(&static_< X_construct<int> >::object);


void pstade_minimal_test()
{
    int x = construct_int(3);
    BOOST_CHECK(x == 3);
}
