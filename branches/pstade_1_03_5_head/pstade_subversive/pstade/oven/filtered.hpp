#ifndef PSTADE_OVEN_FILTERED_HPP
#define PSTADE_OVEN_FILTERED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Eric Niebler, filter_range, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace filtered_detail {


    template< class Range, class Predicate >
    struct baby
    {
        typedef
            boost::filter_iterator<
                typename pass_by_value<Predicate>::type,
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng, Predicate& pred) const
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
         
            return result_type(
                iter_t(pred, boost::begin(rng), boost::end(rng)),
                iter_t(pred, boost::end(rng),   boost::end(rng))
            );
        }
    };


} // namespace filtered_detail


PSTADE_FUNCTION(make_filtered, (filtered_detail::baby<_, _>))
PSTADE_PIPABLE(filtered, (op_make_filtered))


} } // namespace pstade::oven


#endif
