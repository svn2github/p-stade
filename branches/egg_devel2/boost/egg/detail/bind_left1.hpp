#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_BIND_LEFT1_HPP
#define BOOST_EGG_DETAIL_BIND_LEFT1_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bind_left1(f, a1)(a2, a3)
//   is equivalent to f(a1, a2, a3).
// Notice curry2 expects it to work as "normal" bind,
// meaning that by_value is needed.
//
// Note that this can't use `variadic` because of msvc error C1054.


#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/uncapture.hpp>


namespace boost { namespace egg { namespace details {


    template<class Fun, class Arg, class Target>
    struct little_bind_left1_result
    {
        Fun m_fun;
        Arg m_arg;

        // For currying, Arg is the base FunctionObject!
        Arg const &base() const
        {
            return m_arg;
        }

        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PP_DEC(BOOST_EGG_MAX_ARITY), <boost/egg/detail/bind_left1.hpp>))
        #include BOOST_PP_ITERATE()
    };


    template<class Fun, class Arg, class Target>
    struct result_of_bind_left1
    {
        typedef
            function<little_bind_left1_result<Fun, Arg, Target>, by_perfect>
        type;
    };

    #define BOOST_EGG_BIND_LEFT1_L { {
    #define BOOST_EGG_BIND_LEFT1_R } }
    #define BOOST_EGG_BIND_LEFT1(F, A) BOOST_EGG_BIND_LEFT1_L F , A BOOST_EGG_BIND_LEFT1_R


    template<class Target>
    struct X_bind_left1 : derived_from_eval<
        generator<
            typename result_of_bind_left1<deduce<mpl::_1, as_value>, deduce<mpl::_2, as_value>, Target>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of_<
            Fun const(typename uncapture_if<is_same<Fun, Target>, Arg>::result_type, BOOST_EGG_PP_ENUM_PARAMS_WITH(n, A, &))
        >
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return m_fun(uncapture_if<is_same<Fun, Target>, Arg>()(m_arg), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
