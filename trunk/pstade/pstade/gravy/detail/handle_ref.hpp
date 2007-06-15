#ifndef PSTADE_GRAVY_DETAIL_HANDLE_REF_HPP
#define PSTADE_GRAVY_DETAIL_HANDLE_REF_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>


namespace pstade { namespace gravy { namespace detail {


    template<class Handle, class Assertion>
    struct handle_ref
    {
        /*implicit*/ handle_ref(Handle handle) :
            m_handle(handle)
        {
            BOOST_ASSERT(invariant());
        }

        template<class X> // for 'WTL::CHandleXXX' etc
        handle_ref(X const& x, typename enable_if< is_convertible<X, Handle> >::type = 0) :
            m_handle(x)
        {
            BOOST_ASSERT(invariant());
        }

        operator Handle() const
        {
            BOOST_ASSERT(invariant());
            return m_handle;
        }

        Handle handle() const
        {
            BOOST_ASSERT(invariant());
            return m_handle;
        }

    private:
        Handle m_handle;

        bool invariant() const
        {
            return Assertion()(m_handle);
        }

        handle_ref& operator=(handle_ref const&);
    };


} } } // namespace pstade::gravy::detail


#endif
