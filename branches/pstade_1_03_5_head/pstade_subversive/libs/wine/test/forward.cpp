#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/forward.hpp>


#include <boost/lambda/core.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/as.hpp>

#include <pstade/lambda_result_of.hpp>


struct my_fun_t
{
    template< class T >
    T operator()(T x, T y) const
    {
        return x + y;
    }
};


struct my_fun0_t
{
    int operator()() const
    {
        return 10;
    }
};


template< class FunctorWithResult >
int foo(FunctorWithResult fun)
{
    typename boost::result_of<FunctorWithResult(int)>::type x = fun(1, 2);
    return x;
}


int my_fun1(int x)
{
    return x;
}


void test()
{
    using namespace pstade;
    namespace lambda = boost::lambda;

    ::my_fun_t my_fun;

    {
        BOOST_CHECK( 3 ==
            ::foo( pstade::forward<int>(my_fun) )
        );
    } 

    {
        BOOST_CHECK( 3 ==
            ::foo( pstade::op_forward<int>()(my_fun) )
        );
    }

#if 0
    {
        BOOST_CHECK( 3 ==
            3  ::foo( my_fun|forwarded(boost::type<int>()) )
        );
    }
#endif
    {
        BOOST_CHECK( 3 ==
            lambda::bind( pstade::op_forward<int>()(my_fun), lambda::_1, lambda::_2 )(1|as_ref, 2|as_ref)
        );
    }
    { // make lambda perfect!
        BOOST_CHECK( 3 ==
            pstade::op_forward<>()(
                lambda::bind( pstade::op_forward<int>()(my_fun), lambda::_1, lambda::_2 )
            )(1, 2)
        );
    }

    ::my_fun0_t my_fun0;
    {
        boost::result_of<
            boost::result_of<op_forward<int>(my_fun0_t)>::type()
        >::type result = pstade::op_forward<int>()(my_fun0)();
        BOOST_CHECK( result == 10 );
    }

    {
        BOOST_CHECK( 3 ==
            pstade::forward(&my_fun1)(3)
        );
    }
    {
        BOOST_CHECK( 3 ==
            pstade::op_forward<>()(&my_fun1)(3)
        );
    }

    {
        // (lambda::_1 + lambda::_2)(1, 2); // error
        BOOST_CHECK( 3 == 
            pstade::forward(lambda::_1 + lambda::_2)(1, 2)
        );
        BOOST_CHECK( 3 == 
            pstade::op_forward<>()(lambda::_1 + lambda::_2)(1, 2)
        );
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
