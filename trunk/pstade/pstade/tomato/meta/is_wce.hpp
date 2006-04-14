#ifndef PSTADE_TOMATO_META_IS_WCE_HPP
#define PSTADE_TOMATO_META_IS_WCE_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp> // true_, false_


namespace pstade { namespace tomato {


template< class = void >
struct is_wce :
#ifdef _WIN32_WCE
	boost::mpl::true_ 
#else
	boost::mpl::false_
#endif
{ };


} } // namespace pstade::tomato


#endif
