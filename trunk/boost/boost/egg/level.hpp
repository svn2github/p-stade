#ifndef BOOST_EGG_LEVEL_HPP
#define BOOST_EGG_LEVEL_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // protect
#include <boost/egg/by_cref.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/overloaded.hpp>
#include <boost/egg/static.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace level_detail {


        struct little
        {
            BOOST_EGG_OVERLOADED_PREAMBLE()

            template<class Me, class T>
            struct apply
            {
                typedef T &type;
            };

            template<class Me, class Arg>
            struct apply< Me, lambda::lambda_functor<Arg> const >
            {
                typedef
                    lambda::lambda_functor<
                        lambda::lambda_functor_base<
                            lambda::protect_action,
                            tuples::tuple< lambda::lambda_functor<Arg> >
                        >
                    >
                type;
            };

            template<class Re, class T>
            Re call(BOOST_EGG_OVERLOADED(Re) T &t) const
            {
                return t;
            }

            template<class Re, class Arg>
            Re call(BOOST_EGG_OVERLOADED(Re) lambda::lambda_functor<Arg> const &lam) const
            {
                return
                    lambda::lambda_functor_base<
                        lambda::protect_action,
                        tuples::tuple< lambda::lambda_functor<Arg> >
                    >(tuples::tuple< lambda::lambda_functor<Arg> >(lam));
            }
        };


    } // namespace level


    typedef static_<X_identity<mpl::_1>, by_cref>::type T_level_0;
    BOOST_EGG_CONST((T_level_0), level_0) = BOOST_EGG_STATIC();

    #define BOOST_EGG_LEVEL_1_INIT {{}}
    typedef function<level_detail::little, by_cref> T_level_1;
    BOOST_EGG_CONST((T_level_1), level_1) = BOOST_EGG_LEVEL_1_INIT;

    #define BOOST_EGG_LEVEL_2_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LEVEL_1_INIT, BOOST_EGG_LEVEL_1_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_level_1, T_level_1, use_default, by_cref>::type T_level_2;
    BOOST_EGG_CONST((T_level_2), level_2) = BOOST_EGG_LEVEL_2_INIT;

    #define BOOST_EGG_LEVEL_3_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LEVEL_1_INIT, BOOST_EGG_LEVEL_2_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_level_1, T_level_2, use_default, by_cref>::type T_level_3;
    BOOST_EGG_CONST((T_level_3), level_3) = BOOST_EGG_LEVEL_3_INIT;

    #define BOOST_EGG_LEVEL_4_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LEVEL_1_INIT, BOOST_EGG_LEVEL_3_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_level_1, T_level_3, use_default, by_cref>::type T_level_4;
    BOOST_EGG_CONST((T_level_4), level_4) = BOOST_EGG_LEVEL_4_INIT;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
