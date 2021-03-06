#ifndef BOOST_EGG_UNLAMBDA_HPP
#define BOOST_EGG_UNLAMBDA_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is the same as `perfect`.


#include <boost/egg/const.hpp>
#include <boost/egg/return.hpp>


namespace boost { namespace egg {


    template<class Base>
    struct result_of_unlambda :
        result_of_return<Base>
    { };

    #define BOOST_EGG_UNLAMBDA_L BOOST_EGG_RETURN_L
    #define BOOST_EGG_UNLAMBDA_R BOOST_EGG_RETURN_R
    #define BOOST_EGG_UNLAMBDA(F) BOOST_EGG_UNLAMBDA_L F BOOST_EGG_UNLAMBDA_R


    typedef X_return<>::base_class T_unlambda;
    BOOST_EGG_CONST((T_unlambda), unlambda) = BOOST_EGG_RETURN_INIT;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
