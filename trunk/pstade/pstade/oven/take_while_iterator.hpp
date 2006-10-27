#ifndef PSTADE_OVEN_TAKE_WHILE_ITERATOR_HPP
#define PSTADE_OVEN_TAKE_WHILE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator, class Predicate >
struct take_while_iterator;


namespace take_while_iterator_detail {


    template< class Iterator, class Predicate >
    struct super_
    {
        typedef boost::iterator_adaptor<
            take_while_iterator<Iterator, Predicate>,
            Iterator,
            boost::use_default,
            boost::single_pass_traversal_tag
        > type;
    };


} // namespace take_while_iterator_detail


template< class Iterator, class Predicate >
struct take_while_iterator :
    take_while_iterator_detail::super_<Iterator, Predicate>::type
{
private:
    typedef typename take_while_iterator_detail::super_<Iterator, Predicate>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    take_while_iterator()
    { }

    take_while_iterator(Iterator const& first, Iterator const& last, Predicate const& pred) :
        super_t(first), m_last(last), m_pred(pred)
    {
        check_predicate();
    }

    template< class Iterator_ >
    take_while_iterator(
        take_while_iterator<Iterator_, Predicate> const& other,
        typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_last(other.end()), m_pred(other.predicate())
    { }

    Iterator const& end() const
    {
        return m_last;
    }

    Predicate const& predicate() const
    {
        return m_pred;
    }

private:
    Iterator m_last;
    Predicate m_pred;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
    }

    bool is_end() const
    {
        return this->base() == m_last;
    }

    void check_predicate()
    {
        if (is_end())
            return;

        if (!m_pred(*this->base()))
            this->base_reference() = m_last;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT(!is_end());
        return *this->base();
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        ++this->base_reference();
        check_predicate();
    }
};


template< class Iterator, class Predicate > inline
take_while_iterator<Iterator, Predicate> const
make_take_while_iterator(Iterator const& first, Iterator const& last, Predicate pred)
{
    return take_while_iterator<Iterator, Predicate>(first, last, pred);
}


} } // namespace pstade::oven


#endif
