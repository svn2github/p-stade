#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/unfuse.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/noncopyable.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>


int my_plus(boost::tuples::tuple<int const&, int const&, int const&> tup)
{
    return boost::get<0>(tup) + boost::get<1>(tup) + boost::get<2>(tup);
}


int my_two(boost::tuples::tuple<>)
{
    return 2;
}


struct nc :
    private boost::noncopyable
{ };

int take_nc(boost::tuples::tuple<nc&, nc&>)
{
    return 3;
}


int well_formed(char) { return 1; }


template<class F>
void nullary_result_of_check(F f)
{
    BOOST_MPL_ASSERT((boost::is_same<
        typename boost::result_of<F()>::type,
        int
    >));
}


void pstade_minimal_test()
{
    using namespace pstade;

    {
        BOOST_CHECK(
            unfuse(&::my_plus)(5, 7, 2) == 14
        );
    }
    {
        // ::my_two is known to be nullary.
        BOOST_CHECK(
            op_unfuse<use_nullary_result>()(&::my_two)() == 2
        );

        ::nullary_result_of_check( op_unfuse<use_nullary_result>()(&::my_two) );
    }
    {
        // specify nullary result type explicitly.
        BOOST_CHECK(
            op_unfuse<int>()(&::my_two)() == 2
        );
        
        ::nullary_result_of_check( op_unfuse<int>()(&::my_two) );
    }
    {
        unfuse(&::well_formed);
        op_unfuse<int>()(&::well_formed);
    }
    {
        ::nc x, y;
        BOOST_CHECK( unfuse(&::take_nc)(x, y) == 3 );
    }
}
