#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_TEMPLATE_ARGUMENTS_HPP
#define PSTADE_TEMPLATE_ARGUMENTS_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Can work around ETI of 'boost::mpl::apply'.


// Note:
//
// Hmm, if you include <boost/mpl/at.hpp>, unqualified calls of
// 'begin/end' by Boost.StringAlgorithm break down GCC.
// So, for now, 'template_arguments_of' doesn't return a MPL Sequence.


#include <boost/mpl/aux_/lambda_arity_param.hpp>
#include <boost/mpl/aux_/template_arity.hpp>
#include <boost/mpl/int.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>


#if !defined (PSTADE_ALTERNATIVE_MAX_ARITY)
    #define PSTADE_ALTERNATIVE_MAX_ARITY 5 // for MPL PlaceholderExpression
#endif


namespace pstade {


    namespace template_arguments_detail {


        template<BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_ALTERNATIVE_MAX_ARITY, class T, void)>
        struct vector
        {
            typedef vector type;

        #define PSTADE_typedef_argument(z, N, _) typedef BOOST_PP_CAT(T, N) BOOST_PP_CAT(argument, N);
            BOOST_PP_REPEAT(PSTADE_ALTERNATIVE_MAX_ARITY, PSTADE_typedef_argument, ~)
        #undef  PSTADE_typedef_argument
        };


    } // namespace template_arguments_detail


    // GCC needs arity parameter to succeed at specialization.
#define PSTADE_arity_param() \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM( \
        class Arity = boost::mpl::int_<boost::mpl::aux::template_arity<X>::value> \
    ) \
/**/
#define PSTADE_arity(N) \
    BOOST_MPL_AUX_LAMBDA_ARITY_PARAM(boost::mpl::int_<N>) \
/**/


    template<
        class X
        PSTADE_arity_param()
    >
    struct template_arguments_of
    {
        typedef template_arguments_detail::vector<> type;
    };


    template<
        class Arguments,
        class X
        PSTADE_arity_param()
    >
    struct template_arguments_copy
    {
        typedef X type;
    };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_ALTERNATIVE_MAX_ARITY, <pstade/template_arguments.hpp>))
    #include BOOST_PP_ITERATE()


#undef PSTADE_arity
#undef PSTADE_arity_param


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<
    template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
    BOOST_PP_ENUM_PARAMS(n, class T)
>
struct template_arguments_of<X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n)>
{
    typedef template_arguments_detail::vector<BOOST_PP_ENUM_PARAMS(n, T)> type;
};


template<
    class Arguments,
    template<BOOST_PP_ENUM_PARAMS(n, class _)> class X,
    BOOST_PP_ENUM_PARAMS(n, class T)
>
struct template_arguments_copy<Arguments, X<BOOST_PP_ENUM_PARAMS(n, T)> PSTADE_arity(n)>
{
    typedef X<BOOST_PP_ENUM_PARAMS(n, typename Arguments::argument)> type;
};


#undef n
#endif


