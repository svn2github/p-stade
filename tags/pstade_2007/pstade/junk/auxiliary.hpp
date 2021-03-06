#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_AUXILIARY_HPP
#define PSTADE_AUXILIARY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2004/n1742.pdf


#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/deferred.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    // 0ary

    namespace auxiliary0_detail {

        template<class UnaryFun>
        struct return_op0 :
            callable<return_op0<UnaryFun>, return_op0<UnaryFun> const&>
        {
        // as pipe
            template<class Result>
            Result call() const
            {
                return *this;
            }

        // as function call
            template<class Myself, class A0>
            struct apply :
                boost::result_of<PSTADE_DEFERRED(UnaryFun const)(A0&)>
            { };

            template<class Result, class A0>
            Result call(A0& a0) const
            {
                return m_fun(a0);
            }

        // members
            explicit return_op0()
            { }

            explicit return_op0(UnaryFun fun) :
                m_fun(fun)
            { }

            typedef UnaryFun base_type;

            UnaryFun base() const
            {
                return m_fun;
            }

        private:
            UnaryFun m_fun;
        };

        template<class A0, class UnaryFun> inline
        typename boost::result_of<return_op0<UnaryFun>(A0&)>::type
        operator|(A0& a0, return_op0<UnaryFun> op)
        {
            return op(a0);
        }

        template<class A0, class UnaryFun> inline
        typename boost::result_of<return_op0<UnaryFun>(PSTADE_DEDUCED_CONST(A0)&)>::type
        operator|(A0 const& a0, return_op0<UnaryFun> op)
        {
            return op(a0);
        }

    } // namespace auxiliary0_detail

    PSTADE_OBJECT_GENERATOR(auxiliary0,
        (auxiliary0_detail::return_op0< deduce<_1, as_value> >))


    // 1ary-

#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/auxiliary.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity


    #define PSTADE_AUXILIARY(N, Object, Function) \
        namespace BOOST_PP_CAT(pstade_auxiliary_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::boost::result_of< ::pstade::BOOST_PP_CAT(op_auxiliary, N)(PSTADE_UNPARENTHESIZE(Function)) >::type op; \
        } \
        typedef BOOST_PP_CAT(pstade_auxiliary_workarea_of_, Object)::op BOOST_PP_CAT(op_, Object); \
        PSTADE_CONSTANT(Object, (BOOST_PP_CAT(op_, Object))) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::auxiliary0_detail::return_op0, 1)


#endif
#else
#define n BOOST_PP_ITERATION()


namespace PSTADE_PP_CAT3(auxiliary, n, _detail) {

    template<class Function>
    struct BOOST_PP_CAT(return_op, n) :
        callable< BOOST_PP_CAT(return_op, n)<Function> >
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { };

    // as pipe
        template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
            boost::result_of<
                typename boost::result_of<op_pipable(Function const&)>::type(
                    PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)
                )
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            return pipable(m_fun)(
                BOOST_PP_ENUM_PARAMS(n, a)
            );
        }

    // as function call
        template<class Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), A)> :
            boost::result_of<
                PSTADE_DEFERRED(Function const)(PSTADE_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(n), A, &))
            >
        { };    

        template<class Result, BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(BOOST_PP_INC(n), A, & a)) const
        {
            return m_fun(BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), a));
        }

    // members
        explicit BOOST_PP_CAT(return_op, n)()
        { }

        explicit BOOST_PP_CAT(return_op, n)(Function fun) :
            m_fun(fun)
        { }

        typedef Function base_type;

        Function base() const
        {
            return m_fun;
        }

    private:
        Function m_fun;
    };

} // namespace auxiliary_detail

PSTADE_OBJECT_GENERATOR(BOOST_PP_CAT(auxiliary, n),
    (PSTADE_PP_CAT3(auxiliary, n, _detail)::BOOST_PP_CAT(return_op, n)< deduce<_1, as_value> >))


#undef n
#endif
