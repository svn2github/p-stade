#ifndef PSTADE_OVEN_SCAN_ITERATOR_HPP
#define PSTADE_OVEN_SCAN_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/optional.hpp>


namespace pstade { namespace oven {


template< class Iterator, class State, class BinaryFun >
struct scan_iterator;


namespace scan_iterator_detail {


    template< class Iterator >
    struct traversal :
        boost::detail::minimum_category<
            typename boost::iterator_traversal<Iterator>::type,
            boost::forward_traversal_tag
        >
    { };


    template< class Iterator, class State, class BinaryFun >
    struct super_
    {
        typedef boost::iterator_adaptor<
            scan_iterator<Iterator, State, BinaryFun>,
            Iterator,
            State,
            typename traversal<Iterator>::type,
            State const& // can be reference thanks to 'm_cache'.
        > type;
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

    template< class Iterator_ >
    scan_iterator(
        scan_iterator<Iterator_, State, BinaryFun> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_state(other.state()), m_fun(other.functor())
    { }

    State const& state() const
    {
        return m_state;
    }

    BinaryFun functor() const
    {
        return m_fun;
    }

private:
    State m_state;
    BinaryFun m_fun;
    mutable boost::optional<State> m_cache;

    State call_fun() const
    {
        return m_fun(m_state, *this->base());
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


template< class Iterator, class State, class BinaryFun > inline
scan_iterator<Iterator, State, BinaryFun> const
make_scan_iterator(Iterator const& it, State const& init, BinaryFun fun)
{
    return scan_iterator<Iterator, State, BinaryFun>(it, init, fun);
}


} } // namespace pstade::oven


#endif
