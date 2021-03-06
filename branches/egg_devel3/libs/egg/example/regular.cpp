

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/regular.hpp>
#include <boost/iterator/filter_iterator.hpp>
#include <algorithm> // equal


#include "./using_bll.hpp"
#include "./egg_example.hpp"


//[code_example_regular
void egg_example()
{
    int a1[6] = {1,2,3,4,5,6};
    int a2[3] = {2,4,6};

    BOOST_CHECK(
        std::equal(a2, a2+3,
            boost::make_filter_iterator(regular(bll::_1 % 2 == 0), a1, a1+6) )
    );
}
//]
