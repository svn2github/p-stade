#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_ADAPTED_HPP
#define PSTADE_EGG_ADAPTED_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Modeled after: <boost/detail/function_n.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// Note:
//
// 'callable' is more generic than this whose 'Lambda' can't
// have members, but the definition of 'Lambda' can be simpler.
//
// Now 'NullaryResult' must be passed explicitly.
// Something like 'has_nullary_result' would instantiate
// the invalid type with placeholders.
//
// As the result of overload resolution and 'mpl::apply',
// the both const-qualified and non-const-qualified argument type are
// always passed to Lambda, and then the Lambda is *instantiated*;
// even if the either is never called.
// This might be avoided by using 'template_arguments', though.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/void.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include "./apply_params.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg {


    template<class Lambda>
    struct adapted
    {
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply
        { }; // msvc warns if incomplete.

        // These are redefined in 'apply'.
    #define PSTADE_typedef_default_arg(Z, N, _) typedef boost::mpl::void_ BOOST_PP_CAT(arg, N);
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, PSTADE_typedef_default_arg, ~)
    #undef  PSTADE_typedef_default_arg

        // 1ary-
    #define PSTADE_typedef_arg(Z, N, _) typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(arg, N);
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/adapted.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_typedef_arg
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        BOOST_PP_REPEAT(n, PSTADE_typedef_arg, ~)

        // fixed number 'apply' for lightweight compiling
        typedef typename
            BOOST_PP_CAT(boost::mpl::apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                Lambda, BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, arg)
            >::type
        impl_t;

        typedef typename impl_t::result_type type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename apply<void, BOOST_PP_ENUM_PARAMS(n, A)>::impl_t impl_t;
        return impl_t()(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
