#ifndef BOOST_EGG_CONSTRUCT_HPP
#define BOOST_EGG_CONSTRUCT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/construct_xxx.hpp>


#define  BOOST_EGG_CONSTRUCT_RETURN(T, _, Args) \
    return T(Args); \
/**/
#define  BOOST_EGG_CONSTRUCT_XXX_PARAMS (construct, BOOST_EGG_CONSTRUCT_RETURN)
#include BOOST_EGG_CONSTRUCT_XXX() 


#include <boost/egg/detail/suffix.hpp>
#endif
