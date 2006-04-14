#ifndef PSTADE_MELON_BASECHAR_HPP
#define PSTADE_MELON_BASECHAR_HPP


// PStade.Melon
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include "./ucs4_t.hpp"


namespace pstade { namespace melon {


template<
	class = void
>
struct BaseChar :
	biscuit::or_<
		biscuit::bchrng<ucs4_t, 0x0041, 0x005A>,
		biscuit::bchrng<ucs4_t, 0x0061, 0x007A>
	>
{ };


} } // namespace pstade::melon


#endif
