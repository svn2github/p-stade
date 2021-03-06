#ifndef PSTADE_OVEN_MB_ENCODED_HPP
#define PSTADE_OVEN_MB_ENCODED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_adaptor.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./detail/mb_from_wchar.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_encoded_detail {

    template< class Range >
    struct baby
    {
        typedef
            detail::mb_from_wchar<
                typename range_iterator<Range>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(Range& rng) const
        {
            return result_type(rng);
        }
    };


} // namespace mb_encoded_detail


PSTADE_FUNCTION(make_mb_encoded, (mb_encoded_detail::baby<_>))
PSTADE_PIPABLE(mb_encoded, (op_make_mb_encoded))


} } // namespace pstade::oven


#endif
