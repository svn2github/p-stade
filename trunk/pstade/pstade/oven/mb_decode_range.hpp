#ifndef PSTADE_OVEN_MB_DECODE_RANGE_HPP
#define PSTADE_OVEN_MB_DECODE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/archive/iterators/wchar_from_mb.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace mb_decode_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::archive::iterators::wchar_from_mb<
                typename boost::range_result_iterator<Range>::type
            >
        > type;
    };


} // namespace mb_decode_range_detail


template< class Range >
struct mb_decode_range :
    mb_decode_range_detail::super_<Range>::type
{
private:
    typedef typename mb_decode_range_detail::super_<Range>::type super_t;

public:
    explicit mb_decode_range(Range& rng) :
        super_t(rng)
    { }
};


namespace mb_decode_range_detail {


    struct baby_generator
    {
        template< class Range >
        struct result
        {
            typedef mb_decode_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace mb_decode_range_detail


PSTADE_EGG_FUNCTION(make_mb_decode_range, mb_decode_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(mb_decoded, mb_decode_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::mb_decode_range, 1)


#endif
