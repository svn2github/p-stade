#ifndef BOOST_EGG_DETAIL_BYTAG_TO_HPP
#define BOOST_EGG_DETAIL_BYTAG_TO_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_HAS_RVALUE_REFS
#include <boost/egg/detail/deduced_const.hpp>
#include <boost/egg/detail/ns_const_ref.hpp>


#define BOOST_EGG_BYTAG_TO_SEQ(S, _, Bytag) \
    BOOST_PP_CAT(BOOST_EGG_BYTAG_TO_SEQ_, Bytag)() \
/**/

    #define BOOST_EGG_BYTAG_TO_SEQ_by_perfect() (by_ref)(by_cref)
    #define BOOST_EGG_BYTAG_TO_SEQ_by_ref() (by_ref)
    #define BOOST_EGG_BYTAG_TO_SEQ_by_cref() (by_cref)
    #define BOOST_EGG_BYTAG_TO_SEQ_by_value() (by_value)


#define BOOST_EGG_BYTAG_TO_PARAM(R, _, I, Bytag) \
    BOOST_PP_CAT(BOOST_EGG_BYTAG_TO_PARAM_, Bytag)(I) \
/**/

    #define BOOST_EGG_BYTAG_TO_PARAM_by_ref(I) BOOST_PP_CAT(A, I) & BOOST_PP_CAT(a, I)
    #define BOOST_EGG_BYTAG_TO_PARAM_by_cref(I) BOOST_PP_CAT(A, I) const & BOOST_PP_CAT(a, I)
    #define BOOST_EGG_BYTAG_TO_PARAM_by_value(I) BOOST_PP_CAT(A, I) BOOST_PP_CAT(a, I)
#if defined(BOOST_EGG_HAS_RVALUE_REFS)
    #define BOOST_EGG_BYTAG_TO_PARAM_by_perfect(I) BOOST_PP_CAT(A, I) && BOOST_PP_CAT(a, I)
#endif


#define BOOST_EGG_BYTAG_TO_DEDUCED(R, _, I, Bytag) \
    BOOST_PP_CAT(BOOST_EGG_BYTAG_TO_DEDUCED_, Bytag)(I) \
/**/

    #define BOOST_EGG_BYTAG_TO_DEDUCED_by_ref(I) BOOST_PP_CAT(A, I)
    #define BOOST_EGG_BYTAG_TO_DEDUCED_by_cref(I) BOOST_EGG_DEDUCED_CONST(BOOST_PP_CAT(A, I))
    #define BOOST_EGG_BYTAG_TO_DEDUCED_by_value(I) BOOST_PP_CAT(A, I)
#if defined(BOOST_EGG_HAS_RVALUE_REFS)
    #define BOOST_EGG_BYTAG_TO_DEDUCED_by_perfect(I) typename boost::remove_reference<BOOST_PP_CAT(A, I)>::type
#endif


// For msvc-7.1 bug workaround
//

#define BOOST_EGG_BYTAG_TO_NS_DEDUCED(R, _, I, Bytag) \
    BOOST_PP_CAT(BOOST_EGG_BYTAG_TO_NS_DEDUCED_, Bytag)(I) \
/**/

    #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_by_ref(I) BOOST_PP_CAT(A, I) &
    #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_by_cref(I) BOOST_EGG_NS_CONST_REF(BOOST_PP_CAT(A, I))
    #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_by_value(I) BOOST_PP_CAT(A, I) &


#define BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT(R, _, I, Bytag) \
    BOOST_PP_CAT(BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT_, Bytag)(I) \
/**/

    #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT_by_ref(I) BOOST_PP_CAT(A, I) &
    #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT_by_cref(I) BOOST_PP_CAT(A, I) const &
    // #define BOOST_EGG_BYTAG_TO_NS_DEDUCED_REBUILT_by_value(I) BOOST_PP_CAT(A, I) &


#endif
