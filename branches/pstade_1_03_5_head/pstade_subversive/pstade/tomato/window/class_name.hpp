#ifndef PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP
#define PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A Random Access Traversal Readable Lvalue Range
// that represents a window class name.


#include <cstddef> // size_t
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/require.hpp>
#include <pstade/static_c.hpp>
#include <pstade/to_ref.hpp>
#include "../access.hpp"
#include "../c_str.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


namespace class_name_detail {


    typedef
        static_c<std::size_t, 256>
    buffer_size;

    typedef
        boost::array<TCHAR, buffer_size::value>
    buffer_t;


    template< class = void >
    struct init
    {
        typedef init type;

        explicit init(window_ref wnd)
        {
            PSTADE_REQUIRE(0 !=
                ::GetClassName(wnd, boost::begin(m_buf), buffer_size::value)
            );

            BOOST_ASSERT(oven::contains_zero(m_buf));
        }

    protected:
        buffer_t m_buf;
    };


    template< class = void >
    struct super_ :
        boost::result_of<
            oven::op_as_c_str(buffer_t const&)
        >
    { };


} // namespace class_name_detail


struct class_name :
    private class_name_detail::init<>::type,
    class_name_detail::super_<>::type,
    private boost::noncopyable
{
private:
    typedef class_name_detail::init<>::type init_t; 
    typedef class_name_detail::super_<>::type super_t;

public:
    explicit class_name(window_ref wnd) :
        init_t(wnd),
        super_t(m_buf|to_cref|oven::as_c_str)
    { }

    friend
    TCHAR const *pstade_tomato_c_str(class_name const& self)
    {
        return boost::begin(self.m_buf);
    }
};


} } // namespace pstade::tomato


#endif
