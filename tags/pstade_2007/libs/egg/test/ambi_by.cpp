#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/ambi.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/egg/const.hpp>
#include <pstade/egg/by_cref.hpp>
#include <memory> // auto_ptr


namespace egg = pstade::egg;
using namespace egg;


struct base_plus7
{
    typedef int result_type;

    result_type operator()(int i1, int i2, int i3, int i4, int i5, int i6, int i7) const
    {
        return i1+i2+i3+i4+i5+i6+i7;
    }

    result_type operator()(std::auto_ptr<int> i1, int i2, int i3, int i4, int i5, int i6, int i7) const
    {
        return (*i1)+i2+i3+i4+i5+i6+i7;
    }
};

typedef result_of_ambi6<base_plus7, by_value, by_value>::type T_plus7;
PSTADE_EGG_CONST((T_plus7), plus7) = PSTADE_EGG_AMBI({});


struct base_get5th
{
    typedef int const& result_type;

    result_type operator()(int i1, int i2, int i3, int i4, int const& i5, int i6, int i7) const
    {
        return i5;
    }
};

typedef result_of_ambi6<base_get5th, by_cref>::type T_get5th;
PSTADE_EGG_CONST((T_get5th), get5th) = PSTADE_EGG_AMBI({});


void pstade_minimal_test()
{
    {
        BOOST_CHECK( plus7(1,2,3,4,5,6,7) == 1+2+3+4+5+6+7 );
        BOOST_CHECK( (1|plus7(2,3,4,5,6,7)) == 1+2+3+4+5+6+7 );
        BOOST_CHECK( (plus7(2,3,4,5,6,7)|=1) == 1+2+3+4+5+6+7 );
    }
    {
        BOOST_CHECK( plus7(std::auto_ptr<int>(new int(1)),2,3,4,5,6,7) == 1+2+3+4+5+6+7 );
        BOOST_CHECK( (std::auto_ptr<int>(new int(1))|plus7(2,3,4,5,6,7)) == 1+2+3+4+5+6+7 );
        BOOST_CHECK( (plus7(2,3,4,5,6,7)|=std::auto_ptr<int>(new int(1))) == 1+2+3+4+5+6+7 );
    }
    {
        int i = 5;
        BOOST_CHECK( &(get5th(1,2,3,4,i,6,7)) == &i );
        BOOST_CHECK( &(1|get5th(2,3,4,i,6,7)) == &i );
        BOOST_CHECK( &(get5th(2,3,4,i,6,7)|=1) == &i );
    }
}
