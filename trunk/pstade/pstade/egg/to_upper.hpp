#ifndef PSTADE_EGG_TO_UPPER_HPP
#define PSTADE_EGG_TO_UPPER_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale> // toupper
#include "./detail/char_conversion.hpp"


namespace pstade { namespace egg {

    PSTADE_EGG_CHAR_CONVERSION(to_upper, std::toupper)

} } // namespace pstade::egg


#endif
