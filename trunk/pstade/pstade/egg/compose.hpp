#ifndef PSTADE_EGG_COMPOSE_HPP
#define PSTADE_EGG_COMPOSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./by_value.hpp"
#include "./construct_variadic1.hpp"
#include "./detail/tuple_fuse.hpp"
#include "./generator.hpp"
#include "./variadic.hpp"


namespace pstade { namespace egg {


    // The nullary result type must be explicitly specified.
    // 'result_of<F(result_of<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.


    namespace compose_detail {


        template<class F, class G>
        struct little_result
        {
            F m_f;
            G m_g;

            template<class Me, class Args>
            struct apply :
                result_of<
                    F const(
                        typename result_of<
                            typename result_of<detail::T_tuple_fuse(G const &)>::type(Args &)
                        >::type
                    )
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return m_f(detail::tuple_fuse(m_g)(args));
            }
        };


    } // namespace compose_detail


    template<class F, class G, class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct result_of_compose :
        variadic<
            compose_detail::little_result<F, G>,
            Strategy,
            boost::use_default,
            NullaryResult
        >
    { };

    #define PSTADE_EGG_COMPOSE_L PSTADE_EGG_VARIADIC_L {
    #define PSTADE_EGG_COMPOSE_R } PSTADE_EGG_VARIADIC_R
    #define PSTADE_EGG_COMPOSE(F, T) PSTADE_EGG_COMPOSE_L F , T PSTADE_EGG_COMPOSE_R


    template<class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct X_compose : derived_from_eval<
        generator<
            typename result_of_compose<deduce<mpl_1, as_value>, deduce<mpl_2, as_value>, NullaryResult, Strategy>::type,
            by_value,
            X_construct_variadic1<>
        > >
    { };

    typedef X_compose<>::base_class T_compose;
PSTADE_ADL_BARRIER(compose) {
    PSTADE_POD_CONSTANT((T_compose), compose) = PSTADE_EGG_GENERATOR();
}


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
