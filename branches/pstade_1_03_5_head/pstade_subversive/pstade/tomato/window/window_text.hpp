#ifndef PSTADE_TOMATO_WINDOW_WINDOW_TEXT_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_TEXT_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A Random Access Traversal Readable Lvalue Range
// that represents a window text.


// Design:
//
// Other threads may change the text after calling '::GetWindowTextLength',
// so 'null_terminate_range' is still required.
// Note that there seems no way to know whether 'GetWindowText' was failed or empty.


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/to_ref.hpp>
#include "./window_ref.hpp"


namespace pstade { namespace tomato {


namespace window_text_detail {


    typedef oven::array_range<TCHAR>
    buffer_t;


    template< class = void >
    struct init
    {
        typedef init type;

        explicit init(window_ref wnd) :
            m_buf(1 + ::GetWindowTextLength(wnd))
        {
            ::GetWindowText(wnd,
                boost::begin(m_buf), pstade::copy_construct<int>(oven::distance(m_buf))
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


} // namespace window_text_detail


struct window_text :
    private window_text_detail::init<>::type,
    window_text_detail::super_<>::type,
    private boost::noncopyable
{
private:
    typedef window_text_detail::init<>::type init_t; 
    typedef window_text_detail::super_<>::type super_t;

public:
    explicit window_text(window_ref wnd) :
        init_t(wnd),
        super_t(m_buf|to_cref|oven::as_c_str)
    { }

    friend
    TCHAR const *pstade_tomato_c_str(window_text const& self)
    {
        return boost::begin(self.m_buf);
    }
};


} } // namespace pstade::tomato


#endif
