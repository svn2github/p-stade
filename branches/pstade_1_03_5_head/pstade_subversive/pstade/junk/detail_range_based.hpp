#ifndef PSTADE_OVEN_DETAIL_RANGE_BASED_HPP
#define PSTADE_OVEN_DETAIL_RANGE_BASED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// 'SizeSeq' can be omitted?
//
// See: http://tinyurl.com/vkfa8
//
// comp.lang.c++.moderated
// "Two phase name lookup and signature"


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/for_each.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_OVEN_DETAIL_RANGE_BASED(Xxx, IterBased, ResultFun, SizeSeq) \
    \
    struct BOOST_PP_CAT(op_, Xxx) : \
        ::pstade::callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range, PSTADE_PP_ENUM_PARAMS_WITH(5, class A, = void) > \
        struct apply : \
            PSTADE_UNPARENTHESIZE(ResultFun) \
        { }; \
        \
        BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_DETAIL_RANGE_BASED_call, IterBased, SizeSeq) \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    #define PSTADE_OVEN_DETAIL_RANGE_BASED_call(R, IterBased, Size) \
        template< class Result, class Range BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_PARAMS(Size, class A) > \
        Result call(Range& rng BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_BINARY_PARAMS(Size, A, & a)) const \
        { \
            return IterBased(::boost::begin(rng), ::boost::end(rng) \
                BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_PARAMS(Size, a)); \
        } \
    /**/


#define PSTADE_OVEN_DETAIL_RANGE_BASED_BINARY(Xxx, IterBased, ResultFun, SizeSeq) \
   \
    struct BOOST_PP_CAT(op_, Xxx) : \
        ::pstade::callable<BOOST_PP_CAT(op_, Xxx)> \
    { \
        template< class Myself, class Range1, class Range2, PSTADE_PP_ENUM_PARAMS_WITH(5, class A, = void) > \
        struct apply : \
            PSTADE_UNPARENTHESIZE(ResultFun) \
        { }; \
        \
        BOOST_PP_SEQ_FOR_EACH(PSTADE_OVEN_DETAIL_RANGE_BASED_BINARY_call, IterBased, SizeSeq) \
    }; \
    \
    PSTADE_CONSTANT( Xxx, (BOOST_PP_CAT(op_, Xxx)) ) \
    \
/**/

    #define PSTADE_OVEN_DETAIL_RANGE_BASED_BINARY_call(R, IterBased, Size) \
        template< class Result, class Range1, class Range2 BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_PARAMS(Size, class A) > \
        Result call(Range1& rng1, Range2& rng2 BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_BINARY_PARAMS(Size, A, & a)) const \
        { \
            return IterBased(::boost::begin(rng1), ::boost::end(rng1), ::boost::begin(rng2), ::boost::end(rng2) \
                BOOST_PP_COMMA_IF(Size) BOOST_PP_ENUM_PARAMS(Size, a)); \
        } \
    /**/


#endif
