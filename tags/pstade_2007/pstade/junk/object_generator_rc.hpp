#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OBJECT_GENERATOR_HPP
#define PSTADE_OBJECT_GENERATOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    namespace object_generator_detail {


        struct argument_not_passed;
        

        template< class A, class Default, class F >
        struct deduce :
            boost::mpl::eval_if< boost::is_same<A, argument_not_passed>,
                boost::mpl::identity<Default>,
                F
            >
        { };


        template<
            class Lambda,
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, argument_not_passed)
        >
        struct apply
        {
            typedef Lambda to_t;

            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)<
                    typename remove_cvr<Lambda>::type,
                    BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
                >::type
            result_t;

            typedef typename
                affect_cvr<to_t, result_t>::type
            type;
        };


    } // namespace object_generator_detail


    struct object_generator_error_argument_required;


    typedef boost::mpl::_  from_;
    typedef boost::mpl::_1 from_1;
    typedef boost::mpl::_2 from_2;
    typedef boost::mpl::_3 from_3;


    template< class A, class Default = object_generator_error_argument_required >
    struct deduce_to_value :
        object_generator_detail::deduce<
            A, Default,
            pass_by_value<A>
        >
    { };

    template< class A, class Default = object_generator_error_argument_required >
    struct deduce_to_reference :
        object_generator_detail::deduce<
            A, Default,
            boost::add_reference<A>
        >
    { };

    template< class A, class Default = object_generator_error_argument_required >
    struct deduce_to_qualified :
        object_generator_detail::deduce<
            A, Default,
            boost::mpl::identity<A>
        >
    { };


    template< class Lambda >
    struct object_generator :
        callable< object_generator<Lambda>, typename object_generator_detail::apply<Lambda>::type>
    {

        // PSTADE_CALLABLE_MAX_ARITY (primary)

        template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
        struct apply :
            object_generator_detail::apply< Lambda,
                BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
            >
        { };

        template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
        Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_CALLABLE_MAX_ARITY, A, a) ) const
        {
            return Result( BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, a) );
        }


        // 0ary

        template< class Result >
        Result call( ) const
        {
            return Result( );
        }


        // 1ary

        template< class Myself, class A0 >
        struct apply< Myself, A0 > :
            object_generator_detail::apply< Lambda,
                A0
            >
        { };

        template< class Result, class A0 >
        Result call( A0& a0 ) const
        {
            return Result( a0 );
        }
                

        // 2ary-

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/object_generator2.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity


    }; // object_generator


    #define PSTADE_OBJECT_GENERATOR(G, Lambda) \
        typedef pstade::object_generator< Lambda > BOOST_PP_CAT(op_, G); \
        PSTADE_CONSTANT(G, BOOST_PP_CAT(op_, G)) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE((pstade)(object_generator), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    object_generator_detail::apply< Lambda,
        BOOST_PP_ENUM_PARAMS(n, A)
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
