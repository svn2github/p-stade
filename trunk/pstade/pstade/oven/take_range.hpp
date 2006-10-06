#ifndef PSTADE_OVEN_TAKE_RANGE_HPP
#define PSTADE_OVEN_TAKE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./distance.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class ForwardRange >
struct take_range :
    sub_range_base<ForwardRange>::type,
    private as_lightweight_proxy< take_range<ForwardRange> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sub_range_base<ForwardRange>::type super_t;

public:
    template< class Difference >
    take_range(ForwardRange& rng, Difference d) :
        super_t(boost::begin(rng), boost::next(boost::begin(rng), d))
    {
        BOOST_ASSERT(0 <= d && d <= oven::distance(rng));
    }
};


namespace take_range_detail {


    struct baby_make
    {
        template< class Myself, class ForwardRange, class Difference >
        struct apply
        {
            typedef take_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace take_range_detail


PSTADE_EGG_FUNCTION(make_take_range, take_range_detail::baby_make)
PSTADE_EGG_PIPABLE(taken, take_range_detail::baby_make)


} } // namespace pstade::oven


#endif
