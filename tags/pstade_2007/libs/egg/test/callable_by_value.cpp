#include <pstade/vodka/drink.hpp>


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/callable_by_value.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <memory> // auto_ptr
#include <boost/utility/result_of.hpp>
#include <pstade/unused.hpp>
#include <pstade/test.hpp>


struct baby_foo
{
    template< class Myself, class A0, class A1 = void >
    struct apply
    {
        typedef A0 type;
    };

    template< class Result, class A0, class A1 >
    Result call(A0 a0, A1 a1) const
    {
        return a0 + a1;
    }

    template< class Myself, class A0 >
    struct apply<Myself, A0>
    {
        typedef A0 type;
    };

    template< class Result, class A0 >
    Result call(A0 a0) const
    {
        return a0;
    }

    template< class Result >
    Result call() const
    {
        return '0';
    }
};

typedef pstade::egg::callable_by_value<baby_foo, char> op_foo;
op_foo const foo = op_foo();

PSTADE_TEST_IS_RESULT_OF((int), op_foo(int, int))
PSTADE_TEST_IS_RESULT_OF((int), op_foo(int&, int))
PSTADE_TEST_IS_RESULT_OF((int), op_foo(int const&, int))
PSTADE_TEST_IS_RESULT_OF((std::auto_ptr<int>), op_foo(std::auto_ptr<int>))
PSTADE_TEST_IS_RESULT_OF((char), op_foo())



std::auto_ptr<int> make_auto_ptr()
{
    return std::auto_ptr<int>(new int(3));
}


void pstade_minimal_test()
{
    {
        boost::result_of<op_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == 3 );
    }
    {
        boost::result_of<op_foo(std::auto_ptr<int>)>::type x = foo(make_auto_ptr());
        BOOST_CHECK( *x == 3 );
    }
    {
        boost::result_of<op_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
}
