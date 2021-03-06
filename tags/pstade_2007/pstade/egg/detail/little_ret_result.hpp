#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_RET_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_RET_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This can't be implemented by fusing;
// fuse/unfuse requires a functor to support result_of.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../forward.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class ResultType, class Strategy, class Tag>
    struct little_ret_result
    {
        typedef Base base_type;
        typedef Tag tag_type;

        Base m_base;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            eval_if_use_default< ResultType, result_of<Base const()> >::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_base();
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_ret_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        eval_if_use_default<
            ResultType,
            result_of<Base const(PSTADE_EGG_STRATEGY_FORWARD_ENUM_META_ARGS(n, A, Strategy const))>
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(PSTADE_EGG_STRATEGY_FORWARD_ENUM_ARGS(n, a, Strategy const));
    }


#undef n
#endif
