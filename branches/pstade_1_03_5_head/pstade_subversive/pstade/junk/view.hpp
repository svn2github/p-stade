#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // min, max
#include <memory> // auto_ptr
#include <stdexcept> // runtime_error
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ref.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/apple/atl/win.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/instance.hpp>
#include <pstade/ketchup.hpp>
#include <pstade/is_same.hpp>
#include <pstade/lexical_cast.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/idle_handler.hpp>
#include <pstade/tomato/message_filter.hpp>
#include <pstade/tomato/message_loop.hpp>
#include <pstade/tomato/window/create_result.hpp>
#include <pstade/tomato/window/post_message.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include "./detail/chain_node_mouse_msg.hpp"
#include "./detail/remove_caption.hpp"
#include "./detail/update_layout.hpp"
#include "./dimension.hpp"
#include "./element.hpp"
#include "./rectangle.hpp"
#include "./view_attributes.hpp"


namespace pstade { namespace hamburger {


namespace view_detail {


    template< class ViewT >
    struct impl
    {
        typedef ATL::CWindowImpl<
            ViewT,
            ATL::CWindow,
            ATL::CWinTraits<
                WS_OVERLAPPED|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                WS_EX_APPWINDOW
            >
        > type;
    };


    inline
    rectangle initial_rect(element_node& nd)
    {
        try {
            int left      = pstade::lexical(nd.att(Name_left));
            int width     = pstade::lexical(nd.att(Name_width));
            int top       = pstade::lexical(nd.att(Name_top));
            int height    = pstade::lexical(nd.att(Name_height));
            int maxWidth  = pstade::lexical(nd.att(Name_maxWidth));
            int maxHeight = pstade::lexical(nd.att(Name_maxHeight));

            rectangle rc(
                left, top,
                // Workaround: min/max macro
                left + (std::min)(width, maxWidth), top + (std::min)(height, maxHeight)
            );

            if (!rc.IsRectEmpty())
                return rc;
        }
        catch (std::runtime_error& )
        {
        }

        return ATL::CWindow::rcDefault;
    }


    // 'boost::thread_group' seems unrecommanded.
    PSTADE_INSTANCE(boost::mutex, threads_mutex, value)
    PSTADE_INSTANCE(boost::ptr_vector<boost::thread>, threads, value)


} // namespace view_detail


struct view :
    ketchup::message_processor<view,
        view_detail::impl<view>::type,
        element
    >,
    tomato::message_filter<view>,
    tomato::idle_handler<view>
{
private:
    typedef view_detail::impl<view>::type impl_t;

public:
    explicit view()
    {
        hamburger::set_default_view_attributes(*this);

        std::auto_ptr<boost::thread> pth(new boost::thread(boost::lambda::bind(&view::work, this)));
        m_pthread = pth.get();
        view_detail::threads.push_back(pth.release());
    }

/*
    OnFinalMessage(HWND hWnd) // override
    {
        (*parent()).erase(this);
        pstade::unused(hWnd);
    }
*/

protected:
    void impl_create()
    {
        BOOST_ASSERT(!diet::valid(m_hWnd));

        rectangle rc(view_detail::initial_rect(*this));
        Create(NULL, rc);

        detail::remove_caption(m_hWnd);

        // todo: they are rejected....make it crash!
        //start_message_filter();
        //start_idle_handler();

        ShowWindow(SW_NORMAL);
    }

    HWND impl_window()
    {
        BOOST_ASSERT(diet::valid(m_hWnd));

        return m_hWnd;
    }

private:
friend class tomato::access;
    bool on_idle()
    {
        return false;
    }

    bool pre_translate_message(MSG& msg)
    {
        pstade::unused(msg);
        return false;
    }

friend class ketchup::access;
    LRESULT on_create(LPCREATESTRUCT lpCreateStruct)
    {
    	set_msg_handled(false);
        pstade::unused(lpCreateStruct);
        return tomato::create_success;
    }

    void on_size(UINT uType, dimension sz)
    {
        if (uType == SIZE_MINIMIZED)
            return;

        detail::update_layout(*this, sz);
    }

    void on_lbutton_down(UINT uFlags, point pt)
    {
        tomato::post_message(m_hWnd, WM_CLOSE);
        pstade::unused(uFlags, pt);
    }

    void on_destroy()
    {
        ::PostQuitMessage(1);
        set_msg_handled(false);
    }

    begin_msg_map
    <
        msg_wm_create<&_::on_create>,
        msg_wm_size<&_::on_size>,
        msg_wm_lbuttondown<&_::on_lbutton_down>,
        msg_wm_destroy<&_::on_destroy>,
        detail::chain_node_mouse_msg<>
    >
    end_msg_map;

private:
    boost::thread *m_pthread;

    void work()
    {
        tomato::message_loop loop;
        // message_filtering filteing(this);
        // idle_handling idling(this);
        create();
        loop.run();

        {
           namespace bll = boost::lambda;
           boost::mutex::scoped_lock lock(view_detail::threads_mutex);
           view_detail::threads.erase_if(bll::bind<bool>(is_same, bll::_1, boost::ref(*m_pthread)));
        }
    }
};


inline
void view_join_all()
{
    BOOST_FOREACH (boost::thread& td, view_detail::threads) {
        td.join();
    }
}


namespace view_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<view>("view");
    )


} // namespace view_detail


} } // namespace pstade::hamburger


#endif
