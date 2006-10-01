#ifndef PSTADE_OVEN_MERGE_ITERATOR_HPP
#define PSTADE_OVEN_MERGE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Can be bidirectional?


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp> // iterator_traversal, tags
#include <boost/type_traits/add_reference.hpp>
#include <pstade/egg/function.hpp>


namespace pstade { namespace oven {


template< class Iterator1, class Iterator2 >
struct merge_iterator;


namespace merge_iterator_detail {


    template< class Iterator1, class Iterator2 >
    struct traversal :
        boost::detail::minimum_category<
            boost::forward_traversal_tag,
            typename boost::detail::minimum_category<
                typename boost::iterator_traversal<Iterator1>::type,
                typename boost::iterator_traversal<Iterator2>::type
            >::type
        >
    { };


    template< class Iterator1, class Iterator2 >
    struct super_
    {
        typedef boost::iterator_adaptor<
            merge_iterator<Iterator1, Iterator2>,
            Iterator1,
            boost::use_default,
            typename traversal<Iterator2, Iterator2>::type
        > type;
    };


    struct baby_min_
    {
        template< class Myself, class X, class Y >
        struct apply :
            boost::add_reference<X>
        { };

        template< class Result, class X, class Y >
        Result call(X& x, Y& y)
        {
            return x < y ? x : y;
        }
    };

    PSTADE_EGG_FUNCTION_(min_, baby_min_)


} // namespace merge_iterator_detail


template< class Iterator1, class Iterator2  >
struct merge_iterator :
    merge_iterator_detail::super_<Iterator1, Iterator2>::type
{
private:
    typedef typename merge_iterator_detail::super_<Iterator1, Iterator2>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    merge_iterator()
    { }

    merge_iterator(
        Iterator1 const& it1, Iterator1 const& last1,
        Iterator2 const& it2, Iterator2 const& last2
    ) :
        super_t(it1), m_last1(last1),
        m_it2(it2),   m_last2(last2)
    { }

template< class, class > friend struct merge_iterator;
    template< class Iterator1_, class Iterator2_ >
    merge_iterator(
        merge_iterator<Iterator1_, Iterator2_> const& other,
        typename boost::enable_if_convertible<Iterator1_, Iterator1>::type * = 0,
        typename boost::enable_if_convertible<Iterator2_, Iterator2>::type * = 0
    ) :
        super_t(other.base()), m_last1(other.m_last1), 
        m_it2(other.m_it2),    m_last2(other.m_last2)
    { }

private:
    Iterator1 m_last1;
    Iterator2 m_it2, m_last2;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last1 == other.m_last1 && m_last2 == other.m_last2;
    }

    bool is_end1() const
    {
        return this->base() == m_last1;
    }

    bool is_end2() const
    {
        return m_it2 == m_last2;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (is_end1())
            return *m_it2;
        else if (is_end2())
            return *this->base();
        else
            return merge_iterator_detail::min_(*this->base(), *m_it2);
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base() && m_it2 == other.m_it2;
    }

    void increment()
    {
        BOOST_ASSERT(!(is_end1() && is_end2()));

        if (is_end1())
            ++m_it2;
        else if (is_end2())
            ++this->base_reference();
        else if (*this->base() < *m_it2)
            ++this->base_reference();
        else
            ++m_it2;
    }
};


template< class Iterator1, class Iterator2 > inline
merge_iterator<Iterator1, Iterator2> const
make_merge_iterator(
    Iterator1 const& it1, Iterator1 const& last1,
    Iterator2 const& it2, Iterator2 const& last2)
{
    return merge_iterator<Iterator1, Iterator2>(it1, last1, it2, last2);
}


} } // namespace pstade::oven


#endif
