#ifndef PSTADE_OVEN_MERGE_RANGE_HPP
#define PSTADE_OVEN_MERGE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./merge_iterator.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace merge_range_detail {


    template<
        class Range1, class Range2,
        class Compare
    >
    struct super_
    {
        typedef boost::iterator_range<
            merge_iterator<
                typename range_iterator<Range1>::type,
                typename range_iterator<Range2>::type,
                Compare
            >
        > type;
    };


} // namespace merge_range_detail


template<
    class Range1, class Range2,
    class Compare = less_fun
>
struct merge_range :
    merge_range_detail::super_<Range1, Range2, Compare>::type,
    private as_lightweight_proxy< merge_range<Range1, Range2, Compare> >
{
    typedef Range1 pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range1, SinglePassRangeConcept);
    PSTADE_OVEN_DETAIL_REQUIRES(Range2, SinglePassRangeConcept);
    typedef typename merge_range_detail::super_<Range1, Range2, Compare>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    merge_range(Range1& rng1, Range2& rng2, Compare const& comp = pstade::less) :
        super_t(
            iter_t(boost::begin(rng1), boost::end(rng1), boost::begin(rng2), boost::end(rng2), comp),
            iter_t(boost::end(rng1),   boost::end(rng1), boost::end(rng2),   boost::end(rng2), comp)
        )
    { }
};


namespace merge_range_detail {


    struct baby_make
    {
        template< class Myself, class Range1, class Range2, class Compare = less_fun >
        struct apply
        {
            typedef typename pass_by_value<Compare>::type pred_t;
            typedef merge_range<Range1, Range2, pred_t> const type;
        };

        template< class Result, class Range1, class Range2, class Compare >
        Result call(Range1& rng1, Range2& rng2, Compare& comp)
        {
            return Result(rng1, rng2, comp);
        }

        template< class Result, class Range1, class Range2 >
        Result call(Range1& rng1, Range2& rng2)
        {
            return Result(rng1, rng2);
        }
    };


} // namespace merge_range_detail


PSTADE_EGG_FUNCTION(make_merge_range, merge_range_detail::baby_make)
PSTADE_EGG_PIPABLE(merged, merge_range_detail::baby_make)


} } // namespace pstade::oven


#endif
