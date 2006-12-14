#ifndef PSTADE_OVEN_SLICE_ITERATOR_HPP
#define PSTADE_OVEN_SLICE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Inspired by [1].
// 'm_cache' is necessary for [2].
// It might be interesting to look into [3].
//
// [1] http://d.hatena.ne.jp/yotto-k/20060725
// [2] http://std.dkuug.dk/jtc1/sc22/wg21/docs/lwg-defects.html#198
// [3] boost-sandbox/boost/view/step_iterator.hpp


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/optional.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class RandIter >
struct slice_iterator;


namespace slice_iterator_detail {


    template< class RandIter >
    struct super_
    {
        typedef boost::iterator_adaptor<
            slice_iterator<RandIter>,
            RandIter
        > type;
    };


} // namespace slice_iterator_detail


template< class RandIter >
struct slice_iterator :
    slice_iterator_detail::super_<RandIter>::type
{
    typedef slice_iterator type;

private:
    typedef typename slice_iterator_detail::super_<RandIter>::type super_t;
    typedef typename super_t::difference_type diff_t;
    typedef typename super_t::reference ref_t;

public:
    slice_iterator()
    { }

    slice_iterator(RandIter const& it, diff_t start, diff_t stride) :
        super_t(it), m_start(start), m_stride(stride)
    {
        BOOST_ASSERT(is_valid_start());
    }

    template< class RandIter_ >
    slice_iterator(
        slice_iterator<RandIter_> const& other,
        typename boost::enable_if_convertible<RandIter_, RandIter>::type * = 0
    ) :
        super_t(other.base()), m_start(other.start()), m_stride(other.stride())
    {
        BOOST_ASSERT(is_valid_start());
    }

    diff_t start() const
    {
        return m_start;
    }

    diff_t stride() const
    {
        return m_stride;
    }

private:
    diff_t m_start, m_stride;
    mutable boost::optional<RandIter> m_cache;

    bool is_valid_start() const
    {
        return 0 <= m_start && m_start < m_stride;
    }

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_stride == other.stride() && m_start == other.start();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (!m_cache) {
            m_cache = this->base();
            *m_cache += m_start;
        }

        return **m_cache;
    }

    template< class Other >
    bool equal(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return this->base() == other.base();
    }

    void increment()
    {
        this->base_reference() += m_stride;
        m_cache.reset();
    }

    void decrement()
    {
        this->base_reference() += -m_stride;
        m_cache.reset();
    }

    void advance(diff_t d)
    {
        this->base_reference() += d * m_stride;
        m_cache.reset();
    }

    template< class Other >
    diff_t distance_to(Other const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return (other.base() - this->base()) / m_stride;
    }
};


PSTADE_OBJECT_GENERATOR(make_slice_iterator,
    (slice_iterator< deduce_to_value<from_1> >) const)


} } // namespace pstade::oven


#endif
