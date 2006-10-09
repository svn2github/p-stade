#ifndef PSTADE_OVEN_TAKE_RANGE_HPP
#define PSTADE_OVEN_TAKE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/next_prior.hpp> // next
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct take_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< take_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    take_range(Range& rng, Difference d) :
        super_t(boost::begin(rng), boost::next(boost::begin(rng), d))
    {
        BOOST_ASSERT(0 <= d && d <= oven::distance(rng));
    }

    typedef Range pstade_oven_range_base_type;
};


namespace take_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference >
        struct apply
        {
            typedef take_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d)
        {
            return Result(rng, d);
        }
    };


} // namespace take_range_detail


PSTADE_EGG_FUNCTION(make_take_range, take_range_detail::baby_make)
PSTADE_EGG_PIPABLE(taken, take_range_detail::baby_make)


} } // namespace pstade::oven


#endif
