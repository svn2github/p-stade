

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/starling.hpp>
#include "./egg_test.hpp"


#include <boost/egg/always.hpp>


#include "./using_egg.hpp"


void egg_test()
{
    {
        T_always kestrel;
        BOOST_CHECK( starling(kestrel)(kestrel)(12) == 12 );
    }
}
