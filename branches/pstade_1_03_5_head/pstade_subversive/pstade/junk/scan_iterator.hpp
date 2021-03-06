#ifndef PSTADE_OVEN_SCAN_ITERATOR_HPP
#define PSTADE_OVEN_SCAN_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/optional.hpp>
#include <pstade/as.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/minimum_pure.hpp"


namespace pstade { namespace oven {


template< class Iterator, class State, class BinaryFun >
struct scan_iterator;


namespace scan_iterator_detail {


    template< class Iterator, class State, class BinaryFun >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                scan_iterator<Iterator, State, BinaryFun>,
                Iterator,
                State,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type,
                State const& // can be reference thanks to 'm_cache'.
            >
        type;
    };


} // namespace scan_iterator_detail


template< class Iterator, class State, class BinaryFun >
struct scan_iterator :
    scan_iterator_detail::super_<Iterator, State, BinaryFun>::type
{
private:
    typedef typename scan_iterator_detail::super_<Iterator, State, BinaryFun>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    scan_iterator()
    { }

    scan_iterator(Iterator const& it, State const& init, BinaryFun const& fun) :
        super_t(it), m_state(init), m_fun(fun)
    { }

    template< class I, class S >
    scan_iterator(scan_iterator<I, S, BinaryFun> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0,
        typename boost::enable_if_convertible<S, State>::type    * = 0
    ) :
        super_t(other.base()), m_state(other.state()), m_fun(other.function())
    { }

    State const& state() const
    {
        return m_state;
    }

    BinaryFun const& function() const
    {
        return m_fun;
    }

private:
    State m_state;
    BinaryFun m_fun;
    mutable boost::optional<State> m_cache;

    State call_fun() const
    {
        return m_fun(m_state, as_ref(*this->base()));
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache)
            m_cache = call_fun();

        return *m_cache;
    }

    void increment()
    {
        m_state = call_fun();
        ++this->base_reference();
        m_cache.reset();
    }
};


PSTADE_OBJECT_GENERATOR(make_scan_iterator,
    (scan_iterator< deduce<_1, to_value>, deduce<_2, to_value>, deduce<_3, to_value> >) const)


} } // namespace pstade::oven


#endif
