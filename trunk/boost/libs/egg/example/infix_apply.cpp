#include <boost/egg/pstade/vodka/drink.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include <boost/egg/apply.hpp>
#include <boost/egg/pstade/minimal_test.hpp>

#include <boost/egg/functional.hpp> // negate

using namespace pstade::egg;

void test_apply()
{
    using namespace infix;
//[code_infix_apply_example
BOOST_CHECK(apply(negate, apply(negate, apply(negate, 10))) == -10);
//]
    BOOST_CHECK((negate ^=apply^= 10) == -10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= 10) == 10);
    BOOST_CHECK((negate ^=apply^= negate ^=apply^= negate ^=apply^= 10) == -10);
}


void pstade_minimal_test()
{
    ::test_apply();
}
