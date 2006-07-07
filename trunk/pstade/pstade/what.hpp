#ifndef PSTADE_WHAT_HPP
#define PSTADE_WHAT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>


namespace pstade {


template< class Range > inline
std::string what(std::string tag, Range const& msg)
{
    return
        '<' + tag + '>' +
            oven::sequence_cast<std::string>(msg) +
        "</" + tag + '>'
    ;
}


inline
std::string what(std::string tag, char const *psz)
{
    return pstade::what(tag, psz|oven::null_terminated);
}


inline
std::string what(std::string tag, int n)
{
    return pstade::what(tag, pstade::lexical_cast<std::string>(n));
}


} // namespace pstade


#endif
