#ifndef PSTADE_TOMATO_MENU_SET_MENU_MF_DISABLED_VALUE_HPP
#define PSTADE_TOMATO_MENU_SET_MENU_MF_DISABLED_VALUE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)



#include <boost/mpl/if.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/static_c.hpp>
#include "../is_wce.hpp"


namespace pstade { namespace tomato {


struct mf_disabled :
    boost::mpl::if_< is_wce<>,
        static_c<UINT, MF_DISABLED>,
        static_c<UINT, 0>
    >::type
{ };


} } // namespace pstade::tomato


#endif
