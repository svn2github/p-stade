#ifndef PSTADE_DETAIL_AS_MPL_LAMBDA_HPP
#define PSTADE_DETAIL_AS_MPL_LAMBDA_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a VC8 bug that 'mpl::apply<PlaceholderExpression,..>'
// occasionally fails in the instantiation process of 'boost::result_of'.
//
// These workarounds are known:
//   1. Don't use 'mpl::apply' when possible.
//   2. Hide PlaceholderExpression by using inheritance like <boost/numeric/functional.hpp>.
//   3. Call 'mpl::lambda' in non-deduced context like the following macro. 
//
// If a PlaceholderExpression doesn't have a dependent nested 'type',
// that is to say, it is not a Metafunction with placeholder, 'mpl::apply' seems *not* to fail.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/unparenthesize.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1400) // VC8

    #include <boost/mpl/lambda.hpp>

    #define PSTADE_DETAIL_AS_MPL_LAMBDA(PlaceholderExpr) \
        boost::mpl::lambda< PSTADE_UNPARENTHESIZE(PlaceholderExpr) >::type \
    /**/

#else

    #define PSTADE_DETAIL_AS_MPL_LAMBDA \
        PSTADE_UNPARENTHESIZE \
    /**/

#endif


#endif
