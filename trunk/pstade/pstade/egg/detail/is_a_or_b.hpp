#ifndef PSTADE_EGG_DETAIL_IS_A_OR_B_HPP
#define PSTADE_EGG_DETAIL_IS_A_OR_B_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade { namespace egg { namespace detail {


    template<class T, class A, class B>
    struct is_a_or_b :
        boost::mpl::or_<
            boost::is_same<T, A>,
            boost::is_same<T, B>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
