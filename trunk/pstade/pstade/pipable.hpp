#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_PIPABLE_HPP
#define PSTADE_PIPABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: adaptor_base at Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// You may say preprocessors could be removed by using
// the way shown at "./compose.hpp".
// But such implementation is not as small as the following.
// Also, we must know the exact type passed to 'operator|'.


#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/fuse.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    namespace pipable_detail {


        template< class Function, class Arguments = boost::tuples::tuple<> >
        struct pipe :
            callable< pipe<Function, Arguments>, pipe<Function, Arguments> const& >,
            private nonassignable
        {

            template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
            struct apply
            { };


            // 0ary

            template< class Result >
            Result call( ) const
            {
                return *this;
            }


            // 1ary

            template< class Myself, class A0 >
            struct apply< Myself, A0 >
            {
                typedef pipe< Function,
                    boost::tuples::tuple< A0& >
                > type;
            };

            template< class Result, class A0 >
            Result call( A0& a0 ) const
            {
                return Result( m_fun,
                    typename Result::arguments_type( a0 )
                );
            }


            // 2ary-

            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_CALLABLE_MAX_ARITY, <pstade/pipable.hpp>))
            #include BOOST_PP_ITERATE()


            explicit pipe() // for ForwardIterator
            { }

            explicit pipe(Function const& fun, Arguments const& args = Arguments()) :
                m_fun(fun), m_args(args)
            { }

            typedef Function base_type;
            typedef Arguments arguments_type;

            Function const& base() const
            {
                return m_fun;
            }

            Arguments const& arguments() const
            {
                return m_args;
            }

        private:
            Function m_fun;
            Arguments m_args;

        }; // struct pipe


        template< class Arguments, class A > inline
        boost::tuples::cons<A&, Arguments>
        push_front(Arguments const& args, A& a)
        {
            return boost::tuples::cons<A&, Arguments>(a, args);
        };


        template< class A, class Function, class Arguments >
        struct result_of_output
        {
            typedef typename boost::result_of<op_fuse(Function)>::type fused_f;
            typedef boost::tuples::cons<A&, Arguments> args_t;
            typedef typename boost::result_of<fused_f(args_t)>::type type;
        };

        template< class Result, class A, class Pipe > inline
        Result output(A& a, Pipe const& pi)
        {
            return pstade::fuse(pi.base())(
                pipable_detail::push_front(pi.arguments(), a)
            );
        }


        template< class A, class Function, class Arguments > inline
        typename result_of_output<A, Function, Arguments>::type
        operator|(A& a, pipe<Function, Arguments> const& pi)
        {
            return pipable_detail::output<
                typename result_of_output<A, Function, Arguments>::type
            >(a, pi);
        };

        template< class A, class Function, class Arguments > inline
        typename result_of_output<PSTADE_DEDUCED_CONST(A), Function, Arguments>::type
        operator|(A const& a, pipe<Function, Arguments> const& pi)
        {
            return pipable_detail::output<
                typename result_of_output<PSTADE_DEDUCED_CONST(A), Function, Arguments>::type
            >(a, pi);
        };


    } // namespace pipable_detail


    PSTADE_OBJECT_GENERATOR(pipable, (pipable_detail::pipe< deduce<_1, to_value> >))


    #define PSTADE_PIPABLE(Object, Function) \
        PSTADE_CONSTANT( Object, (::boost::result_of< ::pstade::op_pipable(Function) >::type) ) \
    /**/


    template< class T >
    struct is_pipe_impl :
        boost::mpl::false_
    { };

    template< class Function, class Arguments >
    struct is_pipe_impl< pipable_detail::pipe<Function, Arguments> > :
        boost::mpl::true_
    { };


    template< class T >
    struct is_pipe :
        is_pipe_impl< remove_cvr<T> >
    { };


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(pipable_detail)(pipe), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) >
{
    typedef pipe< Function,
        boost::tuples::tuple< PSTADE_PP_ENUM_REFS(n, A) >
    > type;
};

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS(n, A, a) ) const
{
    return Result( m_fun,
        typename Result::arguments_type( BOOST_PP_ENUM_PARAMS(n, a) )
    );
}


#undef n
#endif
