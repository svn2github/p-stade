

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pack.hpp>
#include <boost/egg/by_ref.hpp>
#include "./egg_test.hpp"


#include <boost/mpl/assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/result_of.hpp>


BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<>,
                 boost::egg::result_of_<boost::egg::T_pack()>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<int&, int const&>,
                 boost::egg::result_of_<boost::egg::T_pack(int&, int)>::type > ));


void test_()
{
    using namespace boost::egg;

    BOOST_CHECK( boost::make_tuple(1,2,3,4,5) == pack(1,2,3,4,5) );
    BOOST_CHECK( boost::make_tuple(1,2,3,4)   == pack(1,2,3,4)   );
    BOOST_CHECK( boost::make_tuple(1,2,3)     == pack(1,2,3)     );
    BOOST_CHECK( boost::make_tuple(1,2)       == pack(1,2)       );
    BOOST_CHECK( boost::make_tuple(1)         == pack(1)         );
    BOOST_CHECK( boost::make_tuple()          == pack()          );

    {
        int m = 5;
        boost::tuples::get<4>(pack(1,2,3,4,m)) = 10;
        BOOST_CHECK(m == 10);
    }
    {
        int x, y, z;
        pack(x, y, z) = pack(1, 2, 3);
        BOOST_CHECK( x == 1 && y == 2 && z == 3 );
    }
}


BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<>,
                 boost::egg::result_of_<boost::egg::X_pack<boost::egg::by_ref>()>::type > ));

BOOST_MPL_ASSERT(( boost::is_same< boost::tuples::tuple<int&, int const&>,
                 boost::egg::result_of_<boost::egg::X_pack<boost::egg::by_ref>(int&, int const&)>::type > ));


void test_ref()
{
    using namespace boost::egg;

    int const i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
    int i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;

    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9) == X_pack<by_ref>()(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9) );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3,i4,i5) == X_pack<by_ref>()(i0,i1,i2,i3,i4,i5) );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3,i4)    == X_pack<by_ref>()(i0,i1,i2,i3,i4)   );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2,i3)       == X_pack<by_ref>()(i0,i1,i2,i3)     );
    BOOST_CHECK( boost::make_tuple(i0,i1,i2)          == X_pack<by_ref>()(i0,i1,i2)       );
    BOOST_CHECK( boost::make_tuple(i0,i1)             == X_pack<by_ref>()(i0,i1)         );
    BOOST_CHECK( boost::make_tuple()                  == X_pack<by_ref>()()          );

    BOOST_CHECK( &(boost::tuples::get<0>(X_pack<by_ref>()(i0,i1,i2,i3,i4,i5))) == &i0 );
    BOOST_CHECK( &(boost::tuples::get<9>(X_pack<by_ref>()(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9))) == &i9 );
}


void egg_test()
{
    test_();
    test_ref();
}
