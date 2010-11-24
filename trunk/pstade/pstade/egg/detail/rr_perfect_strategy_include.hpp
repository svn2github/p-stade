#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_PERFECT_STRATEGY_PARAMS)
    #error Please define PSTADE_EGG_PERFECT_STRATEGY_PARAMS.
#endif
#define PSTADE_stg     BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_PERFECT_STRATEGY_PARAMS)
#define PSTADE_arities BOOST_PP_SEQ_TO_ARRAY(BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_PERFECT_STRATEGY_PARAMS))


namespace pstade { namespace egg {


    template<class T>
    struct rvalue_to_const // rvalue
    {
        typedef T const type;
        template<class U>
        U const &forward(U &x) const { return x; }
    };

    template<class T>
    struct rvalue_to_const<T &> // lvalue
    {
        typedef T type;
        template<class U>
        U &forward(U &x) const { return x; }
    };


    template<class Little>
    struct function<Little, PSTADE_stg>
    {
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const &little() const
        {
            return m_little;
        }

    // 0ary-
    #define PSTADE_forward(Z, N, _) rvalue_to_const<BOOST_PP_CAT(A, N)>().forward(BOOST_PP_CAT(a, N))
        #define  PSTADE_PP_ARRAY_ITERATION_PARAMS (PSTADE_arities, <pstade/egg/detail/rr_perfect_strategy_include.hpp>)
        #include PSTADE_PP_ARRAY_ITERATE()
    #undef  PSTADE_forward
    };


} } // namespace pstade::egg


#undef  PSTADE_arities
#undef  PSTADE_stg
#undef  PSTADE_EGG_PERFECT_STRATEGY_PARAMS


#else
#define n PSTADE_PP_ARRAY_ITERATION()


    PSTADE_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    typename apply_little<
        Little const
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, typename rvalue_to_const<A, >::type BOOST_PP_INTERCEPT)
    >::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &&a)) const
    {
        return call_little(m_little BOOST_PP_ENUM_TRAILING(n, PSTADE_forward, _));
    }


#undef  n
#endif
