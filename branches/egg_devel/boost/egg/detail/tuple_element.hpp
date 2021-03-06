#ifndef BOOST_EGG_DETAIL_TUPLE_ELEMENT_HPP
#define BOOST_EGG_DETAIL_TUPLE_ELEMENT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace boost { namespace egg { namespace details {


    template<int N, class Tuple>
    struct tuple_element :
        tuples::element<N, typename remove_cv<Tuple>::type>
    { };


} } } // namespace boost::egg::details


#endif
