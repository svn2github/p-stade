

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_ref.hpp>
#include "./egg_test.hpp"


#include <string>
#include <memory> // auto_ptr
#include <boost/egg/result_of.hpp>
#include "./check_is_result_of.hpp"
#include <boost/egg/const.hpp>


#include "./using_egg.hpp"


struct little_foo
{
    template< class Me, class A0, class A1 = void >
    struct apply
    {
        typedef A0 type;
    };

    template< class Re, class A0, class A1 >
    Re call(A0& a0, A1 const& a1) const
    {
        return a0 + a1;
    }

    template< class Me, class A0 >
    struct apply<Me, A0>
    {
        typedef A0& type;
    };

    template< class Re, class A0 >
    Re call(A0& a0) const
    {
        return a0;
    }

    typedef char nullary_result_type;

    template< class Re >
    Re call() const
    {
        return '0';
    }
};

typedef function<little_foo, by_ref> T_foo;
BOOST_EGG_CONST((T_foo), foo) = {{}};


CHECK_IS_RESULT_OF(int, T_foo(int&, int&))
CHECK_IS_RESULT_OF(int const, T_foo(int const&, int&))
CHECK_IS_RESULT_OF(int&, T_foo(int&))
CHECK_IS_RESULT_OF(int const&, T_foo(int const&))
CHECK_IS_RESULT_OF(char, T_foo())


struct little_big_arity
{
    template<class Me, class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    struct apply
    {
        typedef A0& type;
    };

    template<class Re, class A0>
    Re call(A0& a0, ...) const
    {
        return a0;
    }
};

typedef function<little_big_arity, by_ref> T_big_arity;
BOOST_EGG_CONST((T_big_arity), big_arity) = {{}};


void egg_test()
{
    {
        int i = 1, j = 2;
        boost::egg::result_of_<T_foo(int&, int&)>::type x = foo(i, j);
        BOOST_CHECK( x == 3 );
    }
    {
        int i = 1;
        boost::egg::result_of_<T_foo(int&)>::type x = foo(i);
        BOOST_CHECK( &i == &x );
    }
    {
        boost::egg::result_of_<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int const i0 = 1, i1 = 1, i2 = 2, i3 = 3, i4 = 4;
        int i5 = 5, i6 = 6, i7 = 7, i8 = 8, i9 = 9;
        BOOST_CHECK( &(big_arity(i0,i1,i2,i3,i4,i5,i6,i7,i8,i9)) == &i0 );
    }
}
