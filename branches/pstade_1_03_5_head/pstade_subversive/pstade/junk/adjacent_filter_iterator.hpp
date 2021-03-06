#ifndef PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP
#define PSTADE_OVEN_ADJACENT_FILTER_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This iterator can't be Mutable, because
// the 'next' function depends on the value referenced.


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <pstade/as.hpp>
#include <pstade/object_generator.hpp>
#include "./detail/constant_reference.hpp"
#include "./detail/pure_traversal.hpp"


namespace pstade { namespace oven {


template< class ForwardIter, class BinaryPred >
struct adjacent_filter_iterator;


namespace adjacent_filter_iterator_detail {


    template< class ForwardIter >
    struct traversal :
        boost::detail::minimum_category<
            boost::forward_traversal_tag,
            typename detail::pure_traversal<ForwardIter>::type
        >
    { };


    template< class ForwardIter, class BinaryPred >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                adjacent_filter_iterator<ForwardIter, BinaryPred>,
                ForwardIter,
                boost::use_default,
                typename traversal<ForwardIter>::type,
                typename detail::constant_reference<ForwardIter>::type
            >
        type;
    };


    template< class ForwardIter, class BinaryPred >
    ForwardIter next(ForwardIter const& first, ForwardIter const& last, BinaryPred pred)
    {
        BOOST_ASSERT(first != last);

        ForwardIter next(first);
        while (++next != last) {
            if (pred(as_ref(*first), as_ref(*next)))
                return next;
        }

        return last;
    }


} // namespace adjacent_filter_iterator_detail


template< class ForwardIter, class BinaryPred >
struct adjacent_filter_iterator :
    adjacent_filter_iterator_detail::super_<ForwardIter, BinaryPred>::type
{
private:
    typedef typename adjacent_filter_iterator_detail::super_<ForwardIter, BinaryPred>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    adjacent_filter_iterator()
    { }

    adjacent_filter_iterator(ForwardIter const& it, BinaryPred const& pred, ForwardIter const& last) :
        super_t(it), m_pred(pred), m_last(last)
    { }

    template< class ForwardIter_ >
    adjacent_filter_iterator(
        adjacent_filter_iterator<ForwardIter_, BinaryPred> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_pred(other.predicate()), m_last(other.end())
    { }

    BinaryPred const& predicate() const
    {
        return m_pred;
    }

    ForwardIter const& end() const
    {
        return m_last;
    }

private:
    BinaryPred m_pred;
    ForwardIter m_last;

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        BOOST_ASSERT("out of range" && this->base() != m_last);
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
        BOOST_ASSERT("out of range" && this->base() != m_last);
        this->base_reference() = adjacent_filter_iterator_detail::next(
            this->base(), m_last, m_pred
        );
    }
};


PSTADE_OBJECT_GENERATOR(make_adjacent_filter_iterator,
    (adjacent_filter_iterator< deduce<_1, to_value>, deduce<_2, to_value> >) const)


} } // namespace pstade::oven


#endif
