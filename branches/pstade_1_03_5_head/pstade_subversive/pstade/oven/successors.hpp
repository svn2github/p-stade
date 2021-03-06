#ifndef PSTADE_OVEN_SUCCESSORS_HPP
#define PSTADE_OVEN_SUCCESSORS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/functional.hpp> // identity
#include <pstade/has_xxx.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/to_ref.hpp>
#include "./concepts.hpp"
#include "./detail/constant_reference.hpp"
#include "./detail/minimum_pure.hpp"
#include "./detail/pure_traversal.hpp"
#include "./do_iter_swap.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace successors_detail {


    namespace here = successors_detail;


    template< class Iterator, class Traversal = typename detail::pure_traversal<Iterator>::type >
    struct assert_not_old_return_op
    {
        Iterator operator()(Iterator now) const
        {
            BOOST_ASSERT("iterator must be advanced." && m_old != now);
            return now;
        }

        explicit assert_not_old_return_op(Iterator old) :
            m_old(old)
        { }

    private:
        Iterator m_old;
    };

    template< class Iterator >
    struct assert_not_old_return_op<Iterator, boost::single_pass_traversal_tag> :
        op_identity
    {
        explicit assert_not_old_return_op(Iterator)
        { }
    };

#if !defined(NDEBUG)
    template< class Iterator > inline
    assert_not_old_return_op<Iterator> assert_not_old(Iterator old)
    {
        return assert_not_old_return_op<Iterator>(old);
    }
#else
    template< class Iterator> inline
    op_identity const& assert_not_old(Iterator)
    {
        return identity;
    }
#endif


    template< class Iterator, class BinaryFun >
    struct succeed_iterator;


    PSTADE_HAS_TYPE(is_constant)


    template< class Iterator, class BinaryFun >
    struct succeed_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                succeed_iterator<Iterator, BinaryFun>,
                Iterator,
                boost::use_default,
                typename detail::minimum_pure<
                    boost::forward_traversal_tag,
                    typename boost::iterator_traversal<Iterator>::type
                >::type,
                typename boost::mpl::eval_if< has_is_constant<BinaryFun>,
                    detail::constant_reference<Iterator>,
                    boost::mpl::identity<boost::use_default>
                >::type
            >
        type;
    };


    template< class Iterator, class BinaryFun >
    struct succeed_iterator :
        succeed_iterator_super<Iterator, BinaryFun>::type
    {
    private:
        typedef typename succeed_iterator_super<Iterator, BinaryFun>::type super_t;
        typedef typename super_t::reference ref_t;

    public:
        succeed_iterator()
        { }

        succeed_iterator(Iterator it, BinaryFun elect, Iterator last) :
            super_t(it), m_elect(elect), m_last(last)
        { }

        template< class F >
        succeed_iterator(succeed_iterator<F, BinaryFun> const& other,
            typename boost::enable_if_convertible<F, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_elect(other.elect()), m_last(other.end())
        { }

        BinaryFun elect() const
        {
            return m_elect;
        }

        Iterator end() const
        {
            return m_last;
        }

    private:
        BinaryFun m_elect;
        Iterator m_last;

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.end();
        }

        bool is_end() const
        {
            return this->base() == m_last;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(!is_end());
            return *this->base();
        }

        template< class F >
        bool equal(succeed_iterator<F, BinaryFun> const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return this->base() == other.base();
        }

        void increment()
        {
            BOOST_ASSERT(!is_end());
            this->base_reference() = here::assert_not_old(this->base())(
                m_elect(this->base(), to_cref(m_last))
            );
        }
    };


    template< class F, class B > inline
    void iter_swap(succeed_iterator<F, B> const& left, succeed_iterator<F, B> const& right)
    {
        do_iter_swap(left.base(), right.base());
    }


    template< class Range, class BinaryFun >
    struct baby
    {
        typedef
            succeed_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<BinaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, BinaryFun& elect) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result_type(
               iter_t(boost::begin(rng), elect, boost::end(rng)),
               iter_t(boost::end(rng),   elect, boost::end(rng))
            );
        }
    };


} // namespace successors_detail


PSTADE_FUNCTION(make_successors, (successors_detail::baby<_, _>))
PSTADE_PIPABLE(successors, (op_make_successors))


} } // namespace pstade::oven


#endif

