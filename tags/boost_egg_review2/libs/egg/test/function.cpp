

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function.hpp>
#include "./egg_test.hpp"


#include BOOST_EGG_SUPPRESS_WARNING_BEGIN()
#include <string>
#include <boost/egg/result_of.hpp>
#include "./check_is_result_of.hpp"

#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/egg/const.hpp>
#include BOOST_EGG_SUPPRESS_WARNING_END()


#include "./using_egg.hpp"


struct little_foo
{
    template<class Me, class A0, class A1 = void>
    struct apply
    {
        typedef std::string type;
    };

    template<class Re, class A0, class A1>
    Re call(A0& a0, A1& a1) const
    {
        (void)a0; (void)a1;
        return "2";
    }

    template<class Me, class A0>
    struct apply<Me, A0>
    {
        typedef int type;
    };

    template<class Re, class A0>
    Re call(A0& a0) const
    {
        (void)a0;
        return 1;
    }

    typedef char nullary_result_type;

    template< class Re >
    Re call() const
    {
        return '0';
    }
};

typedef function<little_foo> T_foo;
BOOST_EGG_CONST((T_foo), foo) = BOOST_EGG_FUNCTION({});


CHECK_IS_RESULT_OF(std::string, T_foo(int, double))
CHECK_IS_RESULT_OF(int, T_foo(int))
CHECK_IS_RESULT_OF(char, T_foo())


template< class T0, class T1 >
struct little_bar
{
    template< class Me, class A0, class A1 = void >
    struct apply
    {
        typedef std::string type;
    };

    template< class Re, class A0, class A1 >
    Re call(A0& a0, A1& a1) const
    {
        (void)a0; (void)a1;
        return "2";
    }

    template< class Me, class A0 >
    struct apply<Me, A0>
    {
        typedef int type;
    };

    template< class Re, class A0 >
    Re call(A0& a0) const
    {
        (void)a0;
        return 1;
    }

    typedef char nullary_result_type;

    template< class Re >
    Re call() const
    {
        return '0';
    }
};

template<class T0, class T1>
struct T_bar :
    boost::egg::function< little_bar<T0, T1>, boost::egg::by_perfect >
{ };

BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(T_bar, 2)


struct little_identity
{
    template< class Me, class A0 >
    struct apply
    {
        typedef A0& type;
    };

    template< class Re, class A0 >
    Re call(A0& a0) const
    {
        return a0;
    }
};

typedef boost::egg::function<little_identity, boost::egg::by_perfect> T_identity;
T_identity const identity = { {} };


CHECK_IS_RESULT_OF(int&, T_identity(int&))
CHECK_IS_RESULT_OF(int const&, T_identity(int))
CHECK_IS_RESULT_OF(int const&, T_identity(int const&))
CHECK_IS_RESULT_OF(int const&, T_identity(int const))


struct little_keep_const
{
    template< class Me, class A0 >
    struct apply
    {
        typedef A0 type;
    };

    template< class Re, class A0 >
    Re call(A0& a0) const
    {
        return a0;
    }
};
typedef boost::egg::function<little_keep_const, boost::egg::by_perfect> T_keep_const;
T_keep_const const keep_const = { {} };
BOOST_MPL_ASSERT((boost::is_same< boost::egg::details::unref<boost::egg::by_perfect, int&>::type, int >));
BOOST_MPL_ASSERT((boost::is_same< boost::egg::details::unref<boost::egg::by_perfect, int const&>::type, int const >));
BOOST_MPL_ASSERT((boost::is_same< boost::egg::details::unref<boost::egg::by_perfect, int>::type, int const >));
BOOST_MPL_ASSERT((boost::is_same< boost::egg::details::unref<boost::egg::by_perfect, int const>::type, int const >));
CHECK_IS_RESULT_OF(int, T_keep_const(int&))
CHECK_IS_RESULT_OF(int const, T_keep_const(int))
CHECK_IS_RESULT_OF(int const, T_keep_const(int const&))
CHECK_IS_RESULT_OF(int const, T_keep_const(int const))



void egg_test()
{
    {
        boost::egg::result_of_<T_foo(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );

        int i = 5;
        BOOST_CHECK( boost::lambda::bind(foo, 3, boost::lambda::_1)(i) == "2" );
        BOOST_CHECK( boost::lambda::bind(foo, 3, 2)() == "2" );
    }
    {
        boost::egg::result_of_<T_foo(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );

        int i = 5;
        BOOST_CHECK( boost::lambda::bind(foo, 3)() == 1 );
        BOOST_CHECK( boost::lambda::bind(foo, boost::lambda::_1)(i) == 1 );
    }
    {
        boost::egg::result_of_<T_foo()>::type x = foo();
        BOOST_CHECK( x == '0' );

        BOOST_CHECK( boost::lambda::bind(foo)() == '0' );
    }

    {
        boost::egg::result_of_<T_bar<int, int>(int, int)>::type x = foo(1, 2);
        BOOST_CHECK( x == "2" );
    }
    {
        boost::egg::result_of_<T_bar<int, int>(int)>::type x = foo(1);
        BOOST_CHECK( x == 1 );
    }
    {
        boost::egg::result_of_<T_bar<int, int>()>::type x = foo();
        BOOST_CHECK( x == '0' );
    }
    {
        int i = 10;
        boost::egg::result_of_<T_identity(int&)>::type x = identity(i);
        BOOST_CHECK( &x == &i );
    }
    {
        boost::egg::result_of_<T_keep_const(int)>::type x = keep_const(3);
        (void)x;
    }
}
