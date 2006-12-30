#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_CONSTRUCT_HPP
#define PSTADE_CONSTRUCT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/automatic.hpp>


namespace pstade {


    template<class X>
    struct op_construct :
        callable<op_construct<X>, X>
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        {
            typedef X type;
        };

        // 0ary
        template<class Result>
        Result call() const
        {
            return Result();
        }

        // workaround for vexing parse
        X call() const
        {
            return X();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/construct.hpp>))
        #include BOOST_PP_ITERATE()
    };


    PSTADE_CONSTANT(constructor, (automatic<op_construct<boost::mpl::_1> >))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return Result(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
