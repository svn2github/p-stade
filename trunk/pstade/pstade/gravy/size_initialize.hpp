#ifndef PSTADE_GRAVY_SIZE_INITIALIZE_HPP
#define PSTADE_GRAVY_SIZE_INITIALIZE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
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
// Under VC7.1 optimizer, the code generated by 'x|size_initialize();'
// is the same as 'x.cbSize = sizeof(X);'.


#include <boost/assert.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/auxiliary.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/menuiteminfo_size_v400.hpp"
#include "./detail/is_old_windows.hpp"
#include "./sdk/windows.hpp"


namespace pstade_gravy_extension {

    struct size_initialize { };

}


namespace pstade { namespace gravy {


    namespace size_initialize_detail {


        struct baby
        {
            template<class Myself, class X>
            struct apply :
                boost::add_reference<X>
            { };

            template<class Result, class X>
            Result call(X& x) const
            {
                pstade_gravy_(pstade_gravy_extension::size_initialize(), x);
                return x;
            }
        };


        typedef egg::function<size_initialize_detail::baby> op;


    } // namespace size_initialize_detail


    typedef egg::result_of_auxiliary0<size_initialize_detail::op>::type op_size_initialize;
    PSTADE_POD_CONSTANT((op_size_initialize), size_initialize) = PSTADE_EGG_AUXILIARY({{}} BOOST_PP_EMPTY)();


} } // namespace pstade::gravy


// predefined extensions
//

namespace pstade_gravy_extension {


    template<class X> inline
    void pstade_gravy_(size_initialize, X& x)
    {
        x.cbSize = sizeof(X);
    }


    inline
    void pstade_gravy_(size_initialize, MENUITEMINFO& mii)
    {
        // See: WTL7.5::CMenuItemInfo

        mii.cbSize = sizeof(MENUITEMINFO);

#if (WINVER >= 0x0500)
        // adjust struct size if running on older version of Windows
        if (pstade::gravy::detail::is_old_windows()) {
            BOOST_ASSERT(mii.cbSize > PSTADE_GRAVY_MENUITEMINFO_SIZE_V400); // must be
            mii.cbSize = PSTADE_GRAVY_MENUITEMINFO_SIZE_V400;
        }
#endif
    }


#if !defined(_WIN32_WCE)

    inline
    void pstade_gravy_(size_initialize, WINDOWPLACEMENT& wndpl)
    {
        wndpl.length = sizeof(WINDOWPLACEMENT);
    }

#endif


} // namespace pstade_gravy_extension


#endif
