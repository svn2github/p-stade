#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/fuse.hpp>
#include <pstade/minimal_test.hpp>


#include <boost/noncopyable.hpp>
#include <pstade/tuple.hpp> // tuple_pack


int my_plus(int x, int y, int z)
{
    return x + y + z;
}

int my_two()
{
    return 2;
}


struct nc :
    private boost::noncopyable
{ };

int take_nc(nc&)
{
    return 3;
}


void pstade_minimal_test()
{
    using namespace pstade::egg;

    {
        BOOST_CHECK(
            fuse(&::my_plus)(boost::make_tuple(5, 7, 2)) == 14
        );
    }
    {
        BOOST_CHECK(
            fuse(&::my_two)(boost::make_tuple()) == 2
        );
    }
    {
        ::nc x;
        BOOST_CHECK( fuse(&::take_nc)(pstade::tuple_pack(x)) == 3 );
    }
}
