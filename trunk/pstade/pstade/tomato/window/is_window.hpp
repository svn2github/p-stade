#ifndef PSTADE_TOMATO_WINDOW_IS_WINDOW_HPP
#define PSTADE_TOMATO_WINDOW_IS_WINDOW_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/singleton.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


struct is_window_fun
{
    typedef bool result_type;

    bool operator()(HWND hWnd) const
    {
        pstade::for_debug();
        return ::IsWindow(hWnd)|booleanized;
    }
};


PSTADE_SINGLETON_CONST(is_window_fun, is_window)


} } // namespace pstade::tomato


#endif
