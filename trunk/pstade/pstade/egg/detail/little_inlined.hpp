#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_INLINED_HPP
#define PSTADE_EGG_DETAIL_LITTLE_INLINED_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Clearly variadic<> can't be used, which is difficult for optimizers.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../forward.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Ptr, Ptr ptr, class Strategy>
    struct little_inlined
    {
        typedef typename result_of<Ptr()>::type result_t; // guaranteed to work.

        typedef result_t nullary_result_type;

        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct apply
        {
            typedef result_t type;
        };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_inlined.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return ptr(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef  n
#endif
