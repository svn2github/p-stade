#ifndef PSTADE_EGG_COMPOSE2_HPP
#define PSTADE_EGG_COMPOSE2_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./function_by_cref.hpp"
#include "./function_by_value.hpp"
#include "./fuse.hpp"
#include "./unfuse.hpp"


namespace pstade { namespace egg {


    namespace compose2_detail {


        template<class F, class G1, class G2>
        struct baby_fused_result
        {
            F m_f;
            G1 m_g1;
            G2 m_g2;

            template<class Myself, class ArgTuple>
            struct apply :
                result_of<
                    F const(
                        typename result_of<typename result_of<op_fuse(G1 const&)>::type(ArgTuple const&)>::type,
                        typename result_of<typename result_of<op_fuse(G2 const&)>::type(ArgTuple const&)>::type
                    )
                >
            { };

            template<class Result, class ArgTuple>
            Result call(ArgTuple const& args) const
            {
                return m_f(fuse(m_g1)(args), fuse(m_g2)(args));
            }
        };


    } // namespace compose2_detail


    template<class F, class G1, class G2, class NullaryResult = boost::use_default>
    struct result_of_compose2 :
        result_of_unfuse<
            function_by_cref< compose2_detail::baby_fused_result<F, G1, G2> >,
            boost::use_default,
            NullaryResult
        >
    { };


    // PSTADE_EGG_UNFUSE_L { { F, G1, G2 } } PSTADE_EGG_UNFUSE_M {} PSTADE_EGG_UNFUSE_R
    #define PSTADE_EGG_COMPOSE2_L  PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_COMPOSE2_M1 ,
    #define PSTADE_EGG_COMPOSE2_M2 ,
    #define PSTADE_EGG_COMPOSE2_R  } } PSTADE_EGG_UNFUSE_M {} PSTADE_EGG_UNFUSE_R


    template<class NullaryResult = boost::use_default>
    struct tp_compose2
    {
        struct baby
        {
            template<class Myself, class F, class G1, class G2>
            struct apply :
                result_of_compose2<F, G1, G2, NullaryResult>
            { };

            template<class Result, class F, class G1, class G2>
            Result call(F f, G1 g, G2 h) const
            {
                Result r = PSTADE_EGG_COMPOSE2_L f PSTADE_EGG_COMPOSE2_M1 g PSTADE_EGG_COMPOSE2_M2 h PSTADE_EGG_COMPOSE2_R;
                return r;
            }
        };

        typedef function_by_value<baby> type;
    };


    template<class NullaryResult = boost::use_default>
    struct xp_compose2 :
        tp_compose2<NullaryResult>::type
    { };


    typedef tp_compose2<>::type op_compose2;
    PSTADE_POD_CONSTANT((op_compose2), compose2) = {{}};


} } // namespace pstade::egg


#endif