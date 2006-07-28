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
#include <pstade/egg/function.hpp>
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace mb_decode_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::archive::iterators::wchar_from_mb<
                typename range_iterator<Range>::type
            >
        > type;
    };


} // namespace mb_decode_range_detail


template< class Range >
struct mb_decode_range :
    mb_decode_range_detail::super_<Range>::type,
    private lightweight_proxy< mb_decode_range<Range> >
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
        template< class Unused, class Range >
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


#endif
