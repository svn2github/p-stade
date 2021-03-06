

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/move_assign.hpp>
#include "./egg_test.hpp"


#include "./using_egg.hpp"


bool g_customized = false;

namespace my {

    struct klass { };

    inline
    void boost_egg_move_assign(klass& , klass& )
    {
        g_customized = true;
    }
}


void egg_test()
{
    {
        my::klass to;
        move_assign(my::klass(), to);
        BOOST_CHECK(g_customized);
    }
    {
        int i = 10;
        move_assign(3, i);
        BOOST_CHECK(i == 3);
    }
}
