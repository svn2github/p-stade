#ifndef PSTADE_OVEN_BEGIN_END_HPP
#define PSTADE_OVEN_BEGIN_END_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Provides functor version and pipable interface.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/function.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace begin_end_detail {


    template< class Range >
    struct baby_begin
    {
        typedef typename
            range_iterator<Range>::type
        result_type;

        result_type operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    template< class Range >
    struct baby_end
    {
        typedef typename
            range_iterator<Range>::type
        result_type;

        result_type operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    PSTADE_FUNCTION(normal_begin, (baby_begin<_>))
    PSTADE_FUNCTION(normal_end,   (baby_end<_>))


} // namespace begin_end_detail


PSTADE_ADL_BARRIER(begin_end) { // for Boost v1.33 'const_begin/end'

PSTADE_AUXILIARY(0, begin, (begin_end_detail::op_normal_begin))
PSTADE_AUXILIARY(0, end,   (begin_end_detail::op_normal_end))

} // ADL barrier


} } // namespace pstade::oven


#endif
