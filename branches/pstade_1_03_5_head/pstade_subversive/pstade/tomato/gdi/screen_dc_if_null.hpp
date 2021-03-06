#ifndef PSTADE_TOMATO_GDI_SCREEN_DC_IF_NULL_HPP
#define PSTADE_TOMATO_GDI_SCREEN_DC_IF_NULL_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/require.hpp>
#include <pstade/verify.hpp>
#include "./is_dc.hpp"


namespace pstade { namespace tomato {


struct screen_dc_if_null :
    private boost::noncopyable
{
    explicit screen_dc_if_null(HDC hDC) :
        m_hDC(hDC), m_managed(false)
    {
        if (m_hDC == NULL) {
            m_hDC = ::GetDC(NULL);
            PSTADE_REQUIRE(m_hDC != NULL);
            m_managed = true;
        }

        BOOST_ASSERT(tomato::is_dc(m_hDC));
    }

    ~screen_dc_if_null()
    {
        BOOST_ASSERT(tomato::is_dc(m_hDC));

        if (m_managed)
            ::DeleteDC(m_hDC)|verified;
    }

    HDC handle() const
    {
        return m_hDC;
    }

private:
    HDC m_hDC;
    bool m_managed;
};


} } // namespace pstade::tomato


#endif
