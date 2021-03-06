

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/to_shared_ptr.hpp>
#include "./egg_test.hpp"


#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/auto_new.hpp>
#include "./check_is_result_of.hpp"


#include "./using_egg.hpp"
using boost::egg::enable_if_;


template<class T>
struct my_ptr
{
    template<class P>
    explicit my_ptr(P p,
        typename enable_if_< is_to_shared_ptr_param<T, P> >::type = 0)
        : m_ptr(to_shared_ptr(p))
    { }

    boost::shared_ptr<T> m_ptr;
};

CHECK_IS_RESULT_OF(boost::shared_ptr<int>, T_to_shared_ptr(int *))
CHECK_IS_RESULT_OF(boost::shared_ptr<int>, T_to_shared_ptr(std::auto_ptr<int>))
CHECK_IS_RESULT_OF(boost::shared_ptr<int>, T_to_shared_ptr(boost::shared_ptr<int>))


struct B { virtual ~B() { } };
struct D : B { };

CHECK_IS_RESULT_OF(boost::shared_ptr<B>, X_to_shared_ptr<B>(D *))
CHECK_IS_RESULT_OF(boost::shared_ptr<B>, X_to_shared_ptr<B>(std::auto_ptr<D>))
CHECK_IS_RESULT_OF(boost::shared_ptr<B>, X_to_shared_ptr<B>(boost::shared_ptr<D>))



void egg_test()
{
    {
        my_ptr<int> p(new int(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        my_ptr<int> p(X_auto_new<int>()(3));
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
    {
        boost::shared_ptr<int> p_(new int(3));
        my_ptr<int> p(p_);
        BOOST_CHECK( *(p.m_ptr) == 3 );
    }
}
