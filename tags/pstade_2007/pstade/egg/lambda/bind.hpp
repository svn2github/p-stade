#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_LAMBDA_BIND_HPP
#define PSTADE_EGG_LAMBDA_BIND_HPP
#include "../detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/bind.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/pod_constant.hpp>
#include "../baby_apply.hpp"
#include "../by_cref.hpp"
#include "./config.hpp"


namespace pstade { namespace egg {


    namespace lambda_bind_detail {


        struct baby
        {
        // 1ary-
            template<class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_LAMBDA_BIND_MAX_ARITY, A)>
            struct PSTADE_EGG_BABY_APPLY;

        #define PSTADE_bind_tuple_mapper(N) \
            typename boost::lambda::detail::bind_tuple_mapper< \
                BOOST_PP_ENUM_PARAMS(N, const A) \
            >::type \
        /**/
        #define PSTADE_lambda_functor_base(N) \
            boost::lambda::lambda_functor_base< \
                boost::lambda::action<N, boost::lambda::function_action<N> >, \
                PSTADE_bind_tuple_mapper(N) \
            > \
        /**/
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_LAMBDA_BIND_MAX_ARITY, <pstade/egg/lambda/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_lambda_functor_base
        #undef  PSTADE_bind_tuple_mapper
        };


    } // namespace lambda_bind_detail


    typedef function<lambda_bind_detail::baby, by_cref> T_lambda_bind;
    PSTADE_POD_CONSTANT((T_lambda_bind), lambda_bind) = {{}};


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            boost::lambda::lambda_functor<
                PSTADE_lambda_functor_base(n)
            > // const
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return PSTADE_lambda_functor_base(n)(
            PSTADE_bind_tuple_mapper(n)(
                BOOST_PP_ENUM_PARAMS(n, a)
            )
        );
    }


#undef n
#endif
