#ifndef PSTADE_OVEN_CYCLED_HPP
#define PSTADE_OVEN_CYCLED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // ptrdiff_t
#include <limits>
#include <utility> // pair
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp> // prior
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/for_debug.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include <pstade/value_cast.hpp>
#include "./concepts.hpp"
#include "./detail/constant_reference.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace cycled_detail {


    namespace here = cycled_detail;


    template< class Difference >
    std::pair<Difference, Difference> positive_rem_div(Difference const& a, Difference const& b)
    {
        BOOST_ASSERT(b >= 0);

        Difference const q = a / b;
        Difference const r = a % b;
        if (r < 0)
            return std::make_pair(q - 1, r + b);
        else
            return std::make_pair(q, r);
    }


    template< class Iterator >
    bool iter_find(Iterator first, Iterator last, Iterator val)
    {
        for_debug();

        for (; first != last; ++first) {
            if (first == val)
                return true;
        }

        return false;
    }


    template< class ForwardIter, class Incrementable >
    struct cycle_iterator;


    template< class ForwardIter, class Incrementable >
    struct cycle_iterator_super
    {
        typedef
            boost::iterator_adaptor<
                cycle_iterator<ForwardIter, Incrementable>,
                ForwardIter,
                boost::use_default,
                boost::use_default,
                typename detail::constant_reference<ForwardIter>::type
            >
        type;
    };


    template< class ForwardIter, class Incrementable >
    struct cycle_iterator :
        cycle_iterator_super<ForwardIter, Incrementable>::type
    {
    private:
        typedef typename cycle_iterator_super<ForwardIter, Incrementable>::type super_t;
        typedef typename super_t::difference_type diff_t;
        typedef typename super_t::reference ref_t;

    public:
        typedef Incrementable count_type;

        cycle_iterator()
        { }

        cycle_iterator(
            ForwardIter it, Incrementable count,
            ForwardIter first, ForwardIter last
        ) :
            super_t(it), m_count(count),
            m_first(first), m_last(last)
        { }

    template< class, class > friend struct cycle_iterator;
        template< class F, class I >
        cycle_iterator(cycle_iterator<F, I> const& other,
            typename boost::enable_if_convertible<F, ForwardIter>::type * = 0,
            typename boost::enable_if_convertible<I, Incrementable>::type * = 0
        ) :
            super_t(other.base()), m_count(other.m_count),
            m_first(other.m_first), m_last(other.m_last)
        { }

        count_type const& count() const
        {
            return m_count;
        }

    private:
        count_type m_count;
        ForwardIter m_first, m_last;

        bool invariant() const
        {
#if defined(PSTADE_OVEN_TESTS_SAMPLE_RANGES)
            return here::iter_find(m_first, m_last, this->base());
#else
            return true;
#endif
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_first == other.m_first && m_last == other.m_last;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(this->base() != m_last);

            return *this->base();
        }

        template< class F, class I >
        bool equal(cycle_iterator<F, I> const& other) const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(is_compatible(other));

            return this->base() == other.base() && m_count == other.m_count;
        }

        void increment()
        {
            BOOST_ASSERT(invariant());

            if (++this->base_reference() == m_last) {
                this->base_reference() = m_first;
                ++m_count;
            }
        }

        void decrement()
        {
            BOOST_ASSERT(invariant());

            if (this->base() != m_first) {
                --this->base_reference();
            }
            else {
                this->base_reference() = boost::prior(m_last);
                --m_count;
            }
        }

        void advance(diff_t n)
        {
            BOOST_ASSERT(invariant());

            std::pair<diff_t, diff_t> const q_r =
                here::positive_rem_div((this->base() - m_first) + n, m_last - m_first);
            BOOST_ASSERT(0 <= q_r.second);
            BOOST_ASSERT(q_r.second < m_last - m_first);

            this->base_reference() = m_first + q_r.second;
            m_count += pstade::value_cast<count_type>(q_r.first);
        }

        template< class F, class I >
        diff_t distance_to(cycle_iterator<F, I> const& other) const
        {
            BOOST_ASSERT(invariant());
            BOOST_ASSERT(is_compatible(other));

            return ((m_last - m_first) * (other.m_count - m_count)) + (other.base() - this->base());
        }
    };


} // namespace cycled_detail


struct op_make_cycled :
    callable<op_make_cycled>
{
    template< class Myself, class Range, class I = void, class J = std::ptrdiff_t >
    struct apply
    {
        typedef 
            cycled_detail::cycle_iterator<
                typename range_iterator<Range>::type,
                typename pass_by_value<J>::type // Prefer 'J' to 'I'; see "./counting.hpp".
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class I, class J >
    Result call(Range& rng, I& i, J& j) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename Result::iterator iter_t;
        typedef typename iter_t::count_type cnt_t;
        return Result(
            iter_t(boost::begin(rng), pstade::value_cast<cnt_t>(i), boost::begin(rng), boost::end(rng)),
            iter_t(boost::begin(rng), j,                            boost::begin(rng), boost::end(rng))
        );
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, 0, (std::numeric_limits<std::ptrdiff_t>::max)());
    }
};


PSTADE_CONSTANT(make_cycled, (op_make_cycled))
PSTADE_PIPABLE(cycled, (op_make_cycled))


} } // namespace pstade::oven


#endif
