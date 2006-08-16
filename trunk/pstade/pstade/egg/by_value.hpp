#ifndef PSTADE_EGG_BY_VALUE_HPP
#define PSTADE_EGG_BY_VALUE_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/decay.hpp>
#include <boost/type_traits/remove_cv.hpp>


namespace pstade { namespace egg {


template< class T >
struct by_value :
    boost::remove_cv<
        typename boost::decay<T>::type
    >
{ };


} } // namespace pstade::egg


#endif
