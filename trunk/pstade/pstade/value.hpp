#ifndef PSTADE_VALUE_HPP
#define PSTADE_VALUE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>


namespace pstade {


    // Define this without 'callable' nor 'pipable'.
    // They would turn the argument into reference;
    // that's the dark-side of the language in the
    // case of function reference.


    struct op_value
    {
        template< class Signature >
        struct result;

        template< class Self, class A >
        struct result<Self(A)> :
            pass_by_value<A>
        { };

        template< class A >
        A operator()(A a) const
        {
            return a;
        }
    };

    PSTADE_CONSTANT(value, op_value)


    namespace value_detail {

        struct pipe :
            private boost::noncopyable
        { };


        template< class A > inline
        A operator|(A a, pipe const&)
        {
            return a;
        }
        
    } // namespace value_detail

    PSTADE_CONSTANT(to_value, value_detail::pipe)


} // namespace pstade


#endif
