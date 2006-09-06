#ifndef PSTADE_MELON_CDEND_HPP
#define PSTADE_MELON_CDEND_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/primitive/chseq.hpp>


namespace pstade { namespace melon {


template<
    class = void
>
struct CDEnd :
    biscuit::chseq<']',']','>'>
{ };


} } // namespace pstade::melon


#endif
