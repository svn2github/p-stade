#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../forward.hpp"
#include "../function_fwd.hpp"
#include "../fuse.hpp"
#include "../tuple/config.hpp" // PSTADE_EGG_TUPLE_MAX_SIZE
#include "../tuple/prepend.hpp"
#include "./is_a_or_b.hpp"


#define PSTADE_EGG_PIPABLE_MAX_ARITY BOOST_PP_DEC(PSTADE_EGG_TUPLE_MAX_SIZE)


namespace pstade { namespace egg { namespace detail {


namespace pipable_operators {


    namespace here = pipable_operators;


    template<class O, class Base, class Args>
    struct result_of_output :
        result_of<
            typename result_of<
                T_fuse(Base const&)
            >::type(typename result_of<T_tuple_prepend(Args&, O&)>::type)
        >
    { };


    // Fortunately, boost::tuples::null_type is a POD type.

    template<class Base, class Strategy, class OperandBytag, class Args = boost::tuples::null_type>
    struct little_pipable_result
    {
        typedef Args args_type;

        Base m_base;
        Args m_args;

        Base const& base() const
        {
            return m_base;
        }

        template<class O>
        typename result_of_output<O, Base, Args>::type
        output(O& o) const
        {
            return fuse(m_base)(tuple_prepend(m_args, o));
        }

    // 0ary
        typedef
            function<little_pipable_result, Strategy>
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            Result r = { { m_base } };
            return r;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_PIPABLE_MAX_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_PIPABLE_MAX_ARITY, <pstade/egg/detail/little_pipable_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


    struct lookup_pipable_operator { };


    // operator|
    //   msvc-7.1 seems to need lazy_enable_if to keep return type as well-formed as possible.
    //

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
    operator|(O& o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<PSTADE_DEDUCED_CONST(O), Base, Args> >::type
    operator|(O const& o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
    {
        return pi.little().output(o);
    }

    // by_value
    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< boost::is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
    operator|(O o, function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi)
    {
        // For movable types, we can't turn `o` into const-reference.
        return pi.little().output(o);
    }


    // operater|=
    //

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_ref>, result_of_output<O, Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O& o)
    {
        return pi.little().output(o);
    }

    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< is_a_or_b<OperandBytag, by_perfect, by_cref>, result_of_output<PSTADE_DEDUCED_CONST(O), Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O const& o)
    {
        return pi.little().output(o);
    }

    // by_value
    template<class O, class Base, class Strategy, class OperandBytag, class Args> inline
    typename lazy_enable_if< boost::is_same<OperandBytag, by_value>, result_of_output<O, Base, Args> >::type
    operator|=(function<little_pipable_result<Base, Strategy, OperandBytag, Args>, Strategy> const& pi, O o)
    {
        return pi.little().output(o);
    }


} // namespace pipable_operators


    using pipable_operators::little_pipable_result;
    using pipable_operators::lookup_pipable_operator;


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            function<
                little_pipable_result<
                    Base, Strategy, OperandBytag,
                    // Arguments must be copied in case of by_value.
                    // Notice that Boost.Tuple doesn't work with movable types.
                    boost::tuples::tuple<PSTADE_EGG_FORWARDING_META_ARGS(n, A, Strategy const)>
                >,
                Strategy
            >
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename Result::little_type little_t;
        Result r = { { m_base, typename little_t::args_type(BOOST_PP_ENUM_PARAMS(n, a)) } };
        return r;
    }


#undef n
#endif
