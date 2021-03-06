#ifndef BOOST_EGG_SHARED_NEW_HPP
#define BOOST_EGG_SHARED_NEW_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/shared_ptr.hpp>
#include <boost/egg/ptr_new.hpp>
#include <boost/egg/register_nullary_result.hpp>


namespace boost { namespace egg {


    template<class T, class Strategy = use_default>
    struct X_shared_new :
        X_ptr_new<shared_ptr<T>, Strategy>
    { };


} } // namespace boost::egg


BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::X_shared_new, (class)(class))


#include <boost/egg/detail/suffix.hpp>
#endif
