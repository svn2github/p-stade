#ifndef PSTADE_OVEN_SLICE_RANGE_HPP
#define PSTADE_OVEN_SLICE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./distance.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_difference.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class ForwardRange >
struct slice_range :
    sub_range_base<ForwardRange>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename sub_range_base<ForwardRange>::type super_t;
    typedef typename range_difference<ForwardRange>::type diff_t;

public:
    slice_range(ForwardRange& rng, diff_t n, diff_t m) :
        super_t(boost::make_iterator_range(rng, n, m))
    {
        BOOST_ASSERT( oven::distance(rng) >= n+m );
    }
};


namespace slice_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class DifferenceN, class DifferenceM >
        struct result
        {
            typedef slice_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange, class Difference >
        Result call(ForwardRange& rng, Difference n, Difference m)
        {
            return Result(rng, n, m);
        }
    };


} // namespace slice_range_detail


PSTADE_EGG_FUNCTION(make_slice_range, slice_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(sliced, slice_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::slice_range, 1)


#endif
