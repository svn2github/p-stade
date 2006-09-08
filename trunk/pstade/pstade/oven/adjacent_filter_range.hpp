#ifndef PSTADE_OVEN_ADJACENT_FILTER_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_FILTER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./adjacent_filter_iterator.hpp"
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_filter_range_detail {


    template< class ForwardRange, class BinaryPred >
    struct super_
    {
        typedef boost::iterator_range<
            adjacent_filter_iterator<
                typename range_iterator<ForwardRange>::type,
                BinaryPred
            >
        > type;
    };


} // namespace adjacent_filter_range_detail


template< class ForwardRange, class BinaryPred >
struct adjacent_filter_range :
    adjacent_filter_range_detail::super_<ForwardRange, BinaryPred>::type,
    private as_lightweight_proxy< adjacent_filter_range<ForwardRange, BinaryPred> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename adjacent_filter_range_detail::super_<ForwardRange, BinaryPred>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    adjacent_filter_range(ForwardRange& rng, BinaryPred const& pred) :
        super_t(
            iter_t(boost::begin(rng), pred, boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng),   pred, boost::begin(rng), boost::end(rng))
        )
    { }
};


namespace adjacent_filter_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange, class BinaryPred >
        struct result
        {
            typedef typename egg::by_value<BinaryPred>::type pred_t;
            typedef adjacent_filter_range<ForwardRange, pred_t> const type;
        };

        template< class Result, class ForwardRange, class BinaryPred >
        Result call(ForwardRange& rng, BinaryPred& pred)
        {
            return Result(rng, pred);
        }
    };


} // namespace adjacent_filter_range_detail


PSTADE_EGG_FUNCTION(make_adjacent_filter_range, adjacent_filter_range_detail::baby_make)
PSTADE_EGG_PIPABLE(adjacent_filtered, adjacent_filter_range_detail::baby_make)


} } // namespace pstade::oven


#endif
