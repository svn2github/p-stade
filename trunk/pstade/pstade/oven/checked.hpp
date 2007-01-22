#ifndef PSTADE_OVEN_CHECKED_HPP
#define PSTADE_OVEN_CHECKED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./check_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace checked_detail {


    template< class Range >
    struct baby
    {
        typedef
            check_iterator<typename range_iterator<Range>::type>
        iter_t;

        typedef
            iter_range<iter_t> const
        result;

        result call(Range& rng)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

            return result(
                iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng)),
                iter_t(boost::end(rng),   boost::begin(rng), boost::end(rng))
            );
        }
    };


} // namespace checked_detail


PSTADE_FUNCTION(make_checked, (checked_detail::baby<_>))
PSTADE_PIPABLE(checked, (op_make_checked))


} } // namespace pstade::oven


#endif