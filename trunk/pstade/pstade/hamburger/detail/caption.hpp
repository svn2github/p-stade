#ifndef PSTADE_HAMBURGER_DETAIL_CAPTION_HPP
#define PSTADE_HAMBURGER_DETAIL_CAPTION_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Win32 adds caption forcefully when creating window.


#include <boost/assert.hpp>
#include <pstade/apple/atl/win.hpp> // CWindow
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "./element_attributes.hpp"


namespace pstade { namespace hamburger { namespace detail {


namespace caption_detail {


    inline
    void remove(HWND hWnd)
    {
        BOOST_ASSERT(diet::valid(hWnd));

        ATL::CWindow wnd(hWnd);
        wnd.ModifyStyle(WS_CAPTION, 0);
        wnd.SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOMOVE|SWP_NOSIZE|SWP_NOACTIVATE|SWP_NOZORDER|SWP_FRAMECHANGED);
    }


} // namespace caption_detail



template< class Element >
void reset_caption(Element& elem)
{
    if (oven::equals(elem%Name_visible, Value_true))
        caption_detail::remove(*elem.window());
}



} } } // namespace pstade::hamburger::detail


#endif
