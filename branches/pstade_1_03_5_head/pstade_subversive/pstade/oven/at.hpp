#ifndef PSTADE_OVEN_AT_HPP
#define PSTADE_OVEN_AT_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Though 'value_at(rng)' is the same as 'at(rng|rvalues)',
// it should be a primitive function.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace at_detail {


    template< template< class > class F >
    struct op :
        callable< op<F> >
    {
        template< class Myself, class Range, class Difference >
        struct apply :
            F<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng, typename range_difference<Range>::type n) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(0 <= n && n < distance(rng));

            return *(boost::begin(rng) + n);
        }
    };


} // namespace at_detail


PSTADE_AUXILIARY(1, at,       (at_detail::op<range_reference>))
PSTADE_AUXILIARY(1, value_at, (at_detail::op<range_value>))


} } // namespace pstade::oven


#endif
