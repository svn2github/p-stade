#ifndef PSTADE_OVEN_CONCATENATED_HPP
#define PSTADE_OVEN_CONCATENATED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// A LocalIterator must be valid after copying of SegmentIterator.


// References:
//
// [1] M. H. Austern, Segmented Iterators and Hierarchical Algorithms, 2001.
//     http://lafstern.org/matt/segmented.pdf
// [2] Adobe, segmented_iterator, Adobe Open Source, 2007.
//     http://opensource.adobe.com/classadobe_1_1segmented__iterator.html


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/contract.hpp>
#include <pstade/function.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/pipable.hpp>
#include "./begin_end.hpp" // op_begin
#include "./concepts.hpp"
#include "./detail/maybe_contains.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace concatenated_detail {


    template< class SegmentIter >
    struct concat_iterator;


    template< class SegmentIter >
    struct local_iterator :
        boost::result_of<
            op_begin(typename iterator_read<SegmentIter>::type)
        >
    { };


    // See:
    // http://opensource.adobe.com/iterator_8hpp-source.html#l00087
    template< class SegmentIter, class LocalIter >
    struct traversal_of
    {
        typedef typename boost::iterator_traversal<SegmentIter>::type segment_trv_t;
        typedef typename boost::iterator_traversal<LocalIter>::type local_trv_t;

        typedef typename
            boost::mpl::eval_if<
                boost::mpl::and_<
                    is_convertible<segment_trv_t, boost::bidirectional_traversal_tag>,
                    is_convertible<local_trv_t, boost::bidirectional_traversal_tag>
                >,
                boost::mpl::identity<boost::bidirectional_traversal_tag>,
                boost::mpl::eval_if<
                    is_convertible<local_trv_t, boost::forward_traversal_tag>,
                    boost::mpl::identity<boost::forward_traversal_tag>,
                    boost::mpl::identity<local_trv_t>
                >
            >::type
        type;
    };


    template< class SegmentIter >
    struct concat_iterator_super
    {
        typedef typename local_iterator<SegmentIter>::type local_iter_t;

        typedef
            boost::iterator_adaptor<
                concat_iterator<SegmentIter>,
                SegmentIter,
                typename boost::iterator_value<local_iter_t>::type,
                typename traversal_of<SegmentIter, local_iter_t>::type,
                typename boost::iterator_reference<local_iter_t>::type,
                typename boost::iterator_difference<local_iter_t>::type
            >
        type;
    };


    template< class SegmentIter >
    struct concat_iterator :
        concat_iterator_super<SegmentIter>::type
    {
    private:
        typedef typename concat_iterator_super<SegmentIter>::type super_t;
        typedef typename super_t::reference ref_t;
        typedef typename boost::iterator_reference<SegmentIter>::type local_rng_ref_t;

    public:
        typedef SegmentIter segment_iterator;
        typedef typename local_iterator<SegmentIter>::type local_iterator;

        concat_iterator()
        { }

        concat_iterator(SegmentIter it, SegmentIter last) :
            super_t(it), m_last(last)
        {
            PSTADE_CONSTRUCTOR_PRECONDITION (~
            )

            reset_local_forward();
        }

    template< class > friend struct concat_iterator;
        template< class S >
        concat_iterator(concat_iterator<S> const& other,
            typename boost::enable_if_convertible<S, SegmentIter>::type * = 0,
            typename boost::enable_if_convertible<
                typename concat_iterator<S>::local_iterator, local_iterator
            >::type * = 0
        ) :
            super_t(other.base()), m_last(other.m_last),
            m_local(other.m_local)
        {
            PSTADE_CONSTRUCTOR_PRECONDITION (~
            )
        }

        SegmentIter segment() const
        {
            return this->base();
        }

        local_iterator local() const
        {
            return m_local;
        }

    private:
        SegmentIter m_last;
        local_iterator m_local;

        bool segment_is_end() const
        {
            return this->base() == m_last;
        }

        local_rng_ref_t local_range() const
        {
            PSTADE_PRECONDITION (
                (!segment_is_end())
            )

            return read(this->base());
        }

        void reset_local_forward()
        {
            while (!segment_is_end() && boost::empty(local_range()))
                ++this->base_reference();

            if (!segment_is_end())
                m_local = boost::begin(local_range());
        }

        void reset_local_reverse()
        {
            while (boost::empty(local_range()))
                --this->base_reference();

            m_local = boost::end(local_range());
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.m_last;
        }

#if defined(PSTADE_OVEN_TESTS_SAMPLE_RANGES)
        PSTADE_CLASS_INVARIANT (
            // 'm_local' is undefined if 'segment_is_end'.
            (!segment_is_end() ?
                detail::maybe_contains(local_range(), m_local) : true)
        )
#else
        PSTADE_CLASS_INVARIANT (~
        )
#endif

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            PSTADE_PRECONDITION (
                (!segment_is_end())
            )

            return *m_local;
        }

        template< class S >
        bool equal(concat_iterator<S> const& other) const
        {
            PSTADE_PRECONDITION (
                (is_compatible(other))
            )

            return this->base() == other.base() // basic premise
                && (segment_is_end() || m_local == other.m_local);
        }

        void increment()
        {
            PSTADE_PUBLIC_PRECONDITION (
                (!segment_is_end())
            )

            PSTADE_INVARIANT (
                (m_local != boost::end(local_range()))
            )

            ++m_local;

            if (m_local == boost::end(local_range())) {
                ++this->base_reference();
                reset_local_forward();
            }
        }

        void decrement()
        {
            PSTADE_PUBLIC_PRECONDITION (~
            )

            if (segment_is_end() || m_local == boost::begin(local_range())) {
                --this->base_reference();
                reset_local_reverse();
            }

            --m_local;
        }
    };


    template< class S > inline
    void iter_swap(concat_iterator<S> const& left, concat_iterator<S> const& right)
    {
        do_iter_swap(left.local(), right.local());
    }


    template< class SegmentRange >
    struct baby
    {
        typedef
            concat_iterator<
                typename range_iterator<SegmentRange>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(SegmentRange& rngs) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<typename range_value<SegmentRange>::type>));

            return result_type(
                iter_t(boost::begin(rngs), boost::end(rngs)),
                iter_t(boost::end(rngs),   boost::end(rngs))
            );
        }
    };


} // namespace concatenated_detail


PSTADE_FUNCTION(make_concatenated, (concatenated_detail::baby<_>))
PSTADE_PIPABLE(concatenated, (op_make_concatenated))


} } // namespace pstade::oven


#endif
