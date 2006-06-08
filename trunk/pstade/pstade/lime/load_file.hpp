#ifndef PSTADE_LIME_LOAD_FILE_HPP
#define PSTADE_LIME_LOAD_FILE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/file_range.hpp>
#include <pstade/oven/utf8_decode_range.hpp>
#include <pstade/ustring.hpp>
#include "./load.hpp"


namespace pstade { namespace lime {


template< class Node >
void load_file(Node& root, std::string fileName)
{
    // cache for speed
    ustring tmp; {
        oven::file_range<utf8cp_t> frng(fileName);
        oven::copy(
            frng |
                oven::utf8_decoded,
            garlic::back_inserter(tmp)
        );
    }

    lime::load(root, tmp);
}


} } // namespace pstade::lime


#endif
