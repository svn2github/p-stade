#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_CONSTRUCT_HPP
#define PSTADE_EGG_CONSTRUCT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "./apply_decl.hpp"
#include "./by_perfect.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./forward.hpp"
#include "./nullary_result_of.hpp"


namespace pstade { namespace egg {


    namespace construct_detail {


        template<class X, class Strategy>
        struct little
        {
        // 0ary
            typedef X nullary_result_type;

            template<class Result>
            Result call() const
            {
                return Result();
            }

        // 1ary-
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
            struct apply
            {
                typedef X type;
            };

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/construct.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace construct_detail


    template<class X, class Strategy = by_perfect>
    struct X_construct :
        function<construct_detail::little<X, Strategy>, Strategy>
    { };


} } // namespace pstade::egg


#define  PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE_PARAMS (pstade::egg::X_construct, (class))
#include PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE()


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return Result(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef n
#endif
