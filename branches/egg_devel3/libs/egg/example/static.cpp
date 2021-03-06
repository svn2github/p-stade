

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/static.hpp>
#include <boost/egg/apply.hpp>
#include <boost/mpl/always.hpp>
#include <functional> // plus
#include <cstddef> // ptrdiff_t


#include "./egg_example.hpp"


//[code_example_static
typedef static_< std::plus<int> >::type T_my_plus; /*< `T_my_plus` is __POD__, whereas `std::plus<int>` is not. >*/
T_my_plus const my_plus = {{}};

typedef static_<X_apply<by_cref>, by_cref>::type T_my_apply;
T_my_apply const my_apply = {{}};

void egg_example()
{
    BOOST_CHECK( my_apply(my_plus, 1, 2) == 3 );
}
//]
