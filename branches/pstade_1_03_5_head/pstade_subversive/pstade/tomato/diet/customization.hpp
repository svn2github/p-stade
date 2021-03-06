#ifndef PSTADE_TOMATO_DIET_CUSTOMIZATION_HPP
#define PSTADE_TOMATO_DIET_CUSTOMIZATION_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/format.hpp>
#include <cstddef> // ptrdiff_t
#include <pstade/apple/atl/config.hpp> // ATL_VER
#include <pstade/apple/atl/core.hpp> // ::AtlIsValidString
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/app.hpp> // ::IsMenu for eVC
#include <pstade/nullptr.hpp>
#include <pstade/overload.hpp>
#include <pstade/static_c.hpp>
#include <pstade/unused.hpp>
#include "../boolean_cast.hpp"


// HDC
//
inline
bool pstade_diet_is_valid(HDC hDC, pstade::overload<>)
{
    return (hDC != NULL);
}

template< class OStream > inline
void pstade_diet_dump(HDC hDC, OStream& os, pstade::overload<>)
{
    os << boost::format("<HDC><handle>%x</handle></HDC>") % hDC;
}


// HMENU
//
inline 
bool pstade_diet_is_valid(HMENU hMenu, pstade::overload<>)
{
    return ::IsMenu(hMenu)|pstade::tomato::booleanized;
}


template< class OStream > inline
void pstade_diet_dump(HMENU hMenu, OStream& os, pstade::overload<>)
{
    os << boost::format("<HMENU><handle>%x</handle></HMENU>") % hMenu;
}


// HWND
//
inline 
bool pstade_diet_is_valid(HWND hWnd, pstade::overload<>)
{
    return ::IsWindow(hWnd)|pstade::tomato::booleanized;
}

template< class OStream > inline
void pstade_diet_dump(HWND hWnd, OStream& os, pstade::overload<>)
{
    os << boost::format("<HWND><handle>%x</handle></HWND>") % hWnd;
}


// null-terminated string
//   seems not to work under WinXP.
//
inline
bool pstade_diet_is_valid(TCHAR const *psz, pstade::overload<>)
{
    using namespace pstade;

#if !(PSTADE_APPLE_ATL_VER < 0x0700)

    return ATL::AtlIsValidString(psz)|pstade::tomato::booleanized;

#else

    // See: ATL7::AtlIsValidString

    #if defined(NDEBUG)

        return (psz != PSTADE_NULLPTR);

    #else

        if (psz == PSTADE_NULLPTR)
            return false;

        typedef pstade::static_c<std::ptrdiff_t, 1398269> faraway;

        __try {
            TCHAR const *pch = psz;
            TCHAR const *pchEnd = psz + faraway::value - 1;
            TCHAR ch = *(volatile TCHAR *)pch;
            while ((ch != _T('\0')) && (pch != pchEnd)) {
                ++pch;
                ch = *(volatile TCHAR *)pch;

                if (pch == pchEnd) {
                    BOOST_ASSERT("null-terminated string candidate is too long to diagnose." && false);
                }
            }
        }
        __except (EXCEPTION_EXECUTE_HANDLER) {
            return false;
        }

        return true;

    #endif

#endif // !(PSTADE_APPLE_ATL_VER < 0x0700)
}

template< class OStream > inline
void pstade_diet_dump(TCHAR const *psz, OStream& os, pstade::overload<>)
{
    os << boost::format("<cstring><pointer>%x</pointer></cstring>") % static_cast<void const *>(psz);

    pstade::unused(psz);
}


// HINSTANCE
//
inline 
bool pstade_diet_is_valid(HINSTANCE hInst, pstade::overload<>)
{
    return hInst != NULL;
}

template< class OStream > inline
void pstade_diet_dump(HINSTANCE hInst, OStream& os, pstade::overload<>)
{
    os << boost::format("<HINSTANCE><handle>%x</handle></HINSTANCE>") % hInst;
}


#endif
