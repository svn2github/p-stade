#ifndef PSTADE_NAPKIN_DETAIL_BASIC_PLACEHOLDER_HPP
#define PSTADE_NAPKIN_DETAIL_BASIC_PLACEHOLDER_HPP


// PStade.Napkin
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/any.hpp>
//
// Copyright Kevlin Henney, 2000, 2001, 2002. All rights reserved.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <pstade/copy_construct.hpp>
#include <pstade/lexical_cast.hpp>


namespace pstade { namespace napkin { namespace detail {


template< class CharT >
struct basic_placeholder
{
    virtual ~basic_placeholder()
    { } // In fact, shared_ptr emulates 'virtual'.

    template< class OutputStreamable >
    void output(const OutputStreamable& x)
    {
        override_output(
            pstade::copy_construct< std::basic_string<CharT> >(x|lexicalized).c_str()
        );
    }

protected:
    virtual void override_output(const CharT *psz) = 0;
};


} } } // namespace pstade::napkin::detail


#endif
