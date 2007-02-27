#ifndef PSTADE_ENABLE_IF_HPP
#define PSTADE_ENABLE_IF_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::enable_if' using 'void *' seems a mistake?
// GCC makes you write 'enable_if' on function parameter list,
// then, 'void *' that can eat any pointer would be dangerous.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>


namespace pstade {


    namespace enable_if_detail {

        struct klass;

    }

    typedef
        enable_if_detail::klass *
    enabler;


    template< class Cond, class T = enabler > 
    struct enable_if :
        boost::enable_if<Cond, T>
    { };


    template< class Cond, class F > 
    struct lazy_enable_if :
        boost::lazy_enable_if<Cond, F>
    { };


    template< class Cond, class T = enabler > 
    struct disable_if :
        boost::disable_if<Cond, T>
    { };


    template< class Cond, class F > 
    struct lazy_disable_if :
        boost::lazy_disable_if<Cond, F>
    { };


    // Prefer this if indirectly called from 'enable_if'.
    template< class From, class To >
    struct is_convertible_in_enable_if :
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1
        // See the implementation of 'boost::enable_if_convertible'.
        boost::mpl::or_<
            boost::is_same<From, To>,
            boost::is_convertible<From, To>
        >
#else
        boost::is_convertible<From, To>
#endif
    { };


    template< class From, class To >
    struct enable_if< boost::is_convertible<From, To> > :
        enable_if< is_convertible_in_enable_if<From, To> >
    { };


} // namespace pstade


#endif
