#ifndef PSTADE_TOMATO_SIZE_INITIALIZE_HPP
#define PSTADE_TOMATO_SIZE_INITIALIZE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Design:
//
// We should make wrappers for all the structures if possible.
// But, it is impossible.
// It is better to forget such wrappers and remember this function.


// Note:
//
// Under VC7.1 optimizer, the code generated by 'x|size_initialized;'
// is the same as 'x.cbSize = sizeof(X);'.


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_pod.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/user.hpp> // ::AtlIsOldWindows
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>


namespace pstade_tomato_extension {


    struct size_initialize { };


} // namespace pstade_tomato_extension


namespace pstade { namespace tomato {


struct op_size_initialize :
    callable<op_size_initialize>
{
    template< class Myself, class T >
    struct apply :
        boost::add_reference<T>
    { };

    template< class Result, class T >
    Result call(T& x) const
    {
    #if !BOOST_WORKAROUND(BOOST_MSVC, < 1400)  
        BOOST_MPL_ASSERT((boost::is_pod<T>));
    #endif

        pstade_tomato_(pstade_tomato_extension::size_initialize(), x);
        return x;
    }
};


PSTADE_CONSTANT(size_initialize, (op_size_initialize))
PSTADE_PIPABLE(size_initialized, (op_size_initialize))


} } // namespace pstade::tomato


// predefined extensions
//

namespace pstade_tomato_extension {


    template< class T > inline
    void pstade_tomato_(size_initialize, T& x)
    {
        x.cbSize = sizeof(T);
    }


    inline
    void pstade_tomato_(size_initialize, MENUITEMINFO& mii)
    {
        // See: WTL7.5::CMenuItemInfo

        mii.cbSize = sizeof(MENUITEMINFO);

    #if (WINVER >= 0x0500)

        // adjust struct size if running on older version of Windows
        if (::AtlIsOldWindows()) {
            BOOST_ASSERT(mii.cbSize > MENUITEMINFO_SIZE_VERSION_400); // must be
            mii.cbSize = MENUITEMINFO_SIZE_VERSION_400;
        }

    #endif
    }


#if !defined(_WIN32_WCE)

    inline
    void pstade_tomato_(size_initialize, WINDOWPLACEMENT& wndpl)
    {
        wndpl.length = sizeof(WINDOWPLACEMENT);
    }

#endif // !defined(_WIN32_WCE)


} // namespace pstade_tomato_extension


#endif
