#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_CALLABLE_BY_VALUE_HPP
#define PSTADE_CALLABLE_BY_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/callable.hpp>
#include <pstade/lambda_sig.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    PSTADE_ADL_BARRIER(callable_by_value) {


    template<class Derived, class NullaryResult = boost::use_default>
    struct callable_by_value :
        lambda_sig
    {
        typedef typename
            use_default_to< NullaryResult, callable_error_non_nullary<Derived> >::type
        nullary_result_type;

        template<class FunCall>
        struct result
        { };

        // 0ary
        nullary_result_type
        operator()() const
        {
            return derived().BOOST_NESTED_TEMPLATE call<
                nullary_result_type
            >();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/callable_by_value.hpp>))
        #include BOOST_PP_ITERATE()

    private:
        Derived const& derived() const
        {
            return static_cast<Derived const&>(*this);
        }

    }; // struct callable_by_value


    } // ADL barrier


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


private:
    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    struct BOOST_PP_CAT(result, n) :
        Derived::BOOST_NESTED_TEMPLATE apply<
            Derived,
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename pass_by_value<A, >::type)
        >
    { };

public:
    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>
    { };

    template<BOOST_PP_ENUM_PARAMS(n, class A)>
    typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        return derived().BOOST_NESTED_TEMPLATE call<
            typename BOOST_PP_CAT(result, n)<BOOST_PP_ENUM_PARAMS(n, A)>::type
        >(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
