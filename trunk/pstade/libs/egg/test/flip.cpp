#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/callable.hpp>
#include <pstade/egg/object_generator.hpp>
#include <pstade/egg/make_aggregate1.hpp>
#include <pstade/minimal_test.hpp>


#include <pstade/deferred.hpp>
#include <pstade/test.hpp>
#include <pstade/pod_constant.hpp>


template< class BinaryFun >
struct baby_return_op
{
    template< class Myself, class A0, class A1 >
    struct apply :
        boost::result_of<PSTADE_DEFERRED(BinaryFun const)(A1&, A0&)>
    { };

    template< class Result, class A0, class A1 >
    Result call(A0& a0, A1& a1) const
    {
        return m_fun(a1, a0);
    }

    BinaryFun m_fun;
};

typedef
    pstade::egg::object_generator<
        pstade::egg::callable< baby_return_op<boost::mpl::_1> >, pstade::egg::make_aggregate1
    >::type
op_flip;

PSTADE_POD_CONSTANT(flip, (op_flip))


int minus(int a, int b)
{
    return a - b;
}


void pstade_minimal_test()
{
    BOOST_CHECK(::flip(&minus)(0, 1) == 1);
    BOOST_CHECK(::flip(&minus)(1, 0) == -1);
}