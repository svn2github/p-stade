#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_PIPELINE_HPP
#define PSTADE_EGG_PIPELINE_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why not use: 'boost::result_of'
//
// An array reference doesn't work under weird VC++7.1.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/comma_protect.hpp>
#include <pstade/instance.hpp>
#include <pstade/nonassignable.hpp>
#include "./baby_call.hpp"
#include "./baby_result.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_PIPELINE_MAX_ARITY
#include "./detail/pipeliners.hpp"


namespace pstade { namespace egg {


template< class BabyFunction >
struct pipeline :
    private nonassignable
{

    // structors
    //
    BabyFunction m_baby;

    explicit pipeline()
    { }

    explicit pipeline(BabyFunction const& baby) :
        m_baby(baby)
    { }


    // 0ary
    //
    detail::pipeliner0<BabyFunction>
    operator()() const
    {
        return detail::pipeliner0<BabyFunction
        >(m_baby);
    }


    // 1ary -
    //
    #define PSTADE_EGG_call_operator(R, BitSeq) \
        template< BOOST_PP_ENUM_PARAMS(n, class A) > \
        detail::BOOST_PP_CAT(pipeliner, n)<BabyFunction, \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
        > \
        operator()( \
            BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_param, ~, BitSeq) \
        ) const \
        { \
            return detail::BOOST_PP_CAT(pipeliner, n)<BabyFunction, \
                BOOST_PP_SEQ_FOR_EACH_I_R(R, PSTADE_EGG_arg_type, ~, BitSeq) \
            >( m_baby, BOOST_PP_ENUM_PARAMS(n, a) ); \
        } \
    /**/


    #define PSTADE_EGG_arg_type(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) BOOST_PP_CAT(PSTADE_EGG_ac, Bit)(BOOST_PP_CAT(A, Index)) \
    /**/


    #define PSTADE_EGG_param(R, _, Index, Bit) \
        BOOST_PP_COMMA_IF(Index) \
        BOOST_PP_CAT(A, Index) BOOST_PP_CAT(PSTADE_EGG_c, Bit) & BOOST_PP_CAT(a, Index) \
    /**/

                   
    #define PSTADE_EGG_c0
    #define PSTADE_EGG_c1 const


    // Workaround:
    // VC++7.1 is somewhat broken with array reference.
    #define PSTADE_EGG_ac0(X) X
    #define PSTADE_EGG_ac1(X) typename boost::add_const< X >::type


    #define PSTADE_EGG_bits(Z, N, _) ((0)(1))


    #define BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_PIPELINE_MAX_ARITY, <pstade/egg/pipeline.hpp>))
    #include BOOST_PP_ITERATE()


    #undef PSTADE_EGG_bits
    #undef PSTADE_EGG_ac1
    #undef PSTADE_EGG_ac0
    #undef PSTADE_EGG_c1
    #undef PSTADE_EGG_c0
    #undef PSTADE_EGG_param
    #undef PSTADE_EGG_arg_type
    #undef PSTADE_EGG_call_operator


}; // struct pipeline


// passed as is
//
template< class Input, class BabyFunction > inline
typename baby_result1<BabyFunction, Input>::type
operator|(Input& in, pipeline<BabyFunction> const& pl)
{
    pstade::unused(pl);
    return egg::baby_call(pl.m_baby, in);
}

template< class Input, class BabyFunction > inline
typename baby_result1<BabyFunction, typename boost::add_const<Input>::type>::type
operator|(Input const& in, pipeline<BabyFunction> const& pl)
{
    pstade::unused(pl);
    return egg::baby_call(pl.m_baby, in);
}


} } // namespace pstade::egg


#define PSTADE_EGG_PIPELINE(Name, Baby) \
    PSTADE_INSTANCE( \
        pstade::egg::pipeline< PSTADE_COMMA_PROTECT(Baby) > const, \
        Name, value \
    ) \
/**/


#endif
#else
#define n BOOST_PP_ITERATION()


BOOST_PP_SEQ_FOR_EACH_PRODUCT(
    PSTADE_EGG_call_operator,
    BOOST_PP_REPEAT(n, PSTADE_EGG_bits, ~)
)


#undef n
#endif
