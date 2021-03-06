#ifndef BOOST_EGG_MOVE_ASSIGN_HPP
#define BOOST_EGG_MOVE_ASSIGN_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/const.hpp>
#include <boost/egg/do_swap.hpp>


namespace boost { namespace egg {


    // ADL customization point.
    // Note this is in the same namespace as below for a msvc bug.
    template<class From, class To> inline
    void boost_egg_move_assign(From &from, To &to)
    {
        do_swap(to, from);
    }


    struct T_move_assign
    {
        typedef void result_type;

        // `from` can never be a const-qualified object.
        template<class From, class To> inline
        void operator()(From const &from, To &to) const
        {
            boost_egg_move_assign(const_cast<From &>(from), to);
        }
    };

    BOOST_EGG_CONST((T_move_assign), move_assign) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
