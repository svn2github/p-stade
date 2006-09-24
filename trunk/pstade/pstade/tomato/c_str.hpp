#ifndef PSTADE_TOMATO_C_STR_HPP
#define PSTADE_TOMATO_C_STR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/atl/config.hpp> // ATL_VER, CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include <pstade/apple/atl/core.hpp> // ::AtlIsValidString
#include <pstade/apple/atl/simpstr_fwd.hpp> // CSimpleStringT
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/wtl/misc.hpp> // CString
#include <pstade/apple/basic_string_fwd.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/static_c.hpp>
#include "./access.hpp"
#include "./boolean_cast.hpp"


// c_str extension space
//

namespace pstade_tomato_extension {


    struct c_str { };


    PSTADE_METAPREDICATE(intrusive_cstringizable, pstade_tomato)


} // namespace pstade_tomato_extension


namespace pstade { namespace tomato {


// c_str
//

namespace c_str_detail {


    inline
    bool is_valid(TCHAR const *psz)
    {
    #if !(PSTADE_APPLE_ATL_VER < 0x0700)

        return ATL::AtlIsValidString(psz)|booleanized;

    #else

        // See:
        // ATL7::AtlIsValidString

        #if defined(NDEBUG)

            return (psz != PSTADE_NULLPTR);

        #else

            if (psz == PSTADE_NULLPTR)
                return false;

            typedef static_c<std::ptrdiff_t, 1398269> faraway;

            __try {
                TCHAR const *pch = psz;
                TCHAR const *pchEnd = psz + faraway::value - 1;
                TCHAR ch = *(volatile TCHAR *)pch;
                while ((ch != _T('\0')) && (pch != pchEnd)) {
                    ++pch;
                    ch = *(volatile TCHAR *)pch;

                    BOOST_ASSERT("null-terminated string candidate is too long to diagnose." && pch != pchEnd);
                }
            }
            __except (EXCEPTION_EXECUTE_HANDLER) {
                return false;
            }

            return true;

        #endif

    #endif // !(PSTADE_APPLE_ATL_VER < 0x0700)
    }


    using pstade_tomato_extension::is_intrusive_cstringizable;


    // member function
    //
    template< class T > inline
    TCHAR const *aux(T const& str, typename boost::enable_if< is_intrusive_cstringizable<T> >::type * = 0)
    {
        return access::detail_c_str(str);
    }


    // ADL
    //
    template< class T > inline
    TCHAR const *pstade_tomato_c_str(T const& str)
    {
        return pstade_tomato_(pstade_tomato_extension::c_str(), str);
    }

    template< class T > inline
    TCHAR const *aux(T const& str, typename boost::disable_if< is_intrusive_cstringizable<T> >::type * = 0)
    {
        return pstade_tomato_c_str(str);
    }


    struct baby
    {
        template< class Unused, class CStringizable >
        struct apply
        {
            typedef TCHAR const *type;
        };

        // 'has_xxx' works only with "class".
        template< class Result >
        Result call(TCHAR const *psz)
        {
            return psz;
        }

        template< class Result, class CStringizable >
        Result call(CStringizable const& str)
        {
            Result result = c_str_detail::aux(str);
            BOOST_ASSERT(c_str_detail::is_valid(result));
            return result;
        }
    };


} // namespace c_str_detail


PSTADE_EGG_FUNCTION(c_str, c_str_detail::baby)
PSTADE_EGG_PIPABLE(c_stringized, c_str_detail::baby)


template< class T, class Base = boost::mpl::empty_base >
struct as_intrusive_cstringizable :
    pstade_tomato_extension::as_intrusive_cstringizable<T, Base>
{ };


} } // namespace pstade::tomato


// predefined extensions
//

namespace pstade_tomato_extension {


    TCHAR const *
    pstade_tomato_(c_str, WTL::CString const& str)
    {
        return str;
    }


    // 'enable_if<is_ATL_CSimpleStringT,...>' is useless here, which ignores class hierarchy.
    template< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
    BaseType const *
    pstade_tomato_(c_str, ATL::CSimpleStringT< PSTADE_APPLE_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > const& str)
    {
        return str;
    }


    template< class Traits, class Alloc > inline
    TCHAR const *
    pstade_tomato_(c_str, std::basic_string<TCHAR, Traits, Alloc> const& str)
    {
        return str.c_str();
    }


} // namespace pstade_tomato_extension


#endif
