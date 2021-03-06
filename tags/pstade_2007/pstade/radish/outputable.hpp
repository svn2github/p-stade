#ifndef PSTADE_RADISH_OUTPUTABLE_HPP
#define PSTADE_RADISH_OUTPUTABLE_HPP


// PStade.Radish
//
// Copyright MB 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iosfwd> // basic_ostream
#include <pstade/adl_barrier.hpp>
#include "./access.hpp"


namespace pstade { namespace radish { PSTADE_ADL_BARRIER(outputable) {


template< class T >
struct outputable
{
    template< class CharT, class Traits >
    friend
    std::basic_ostream<CharT, Traits>&
    operator<<(std::basic_ostream<CharT, Traits>& os, T const& x)
    {
        access::detail_output(x, os);
        return os;
    }
};


} } } // namespace pstade::radish::ADL_BARRIER


#endif
