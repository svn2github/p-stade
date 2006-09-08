#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/range/iterator_range.hpp>
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <pstade/egg/by_value.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"



namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template< class BidiRange, class U8T >
    struct super_
    {
        typedef boost::iterator_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<BidiRange>::type,
                U8T
            >
        > type;
    };


} // namespace utf8_encode_range_detail


template< class BidiRange, class U8T = boost::uint8_t >
struct utf8_encode_range :
    utf8_encode_range_detail::super_<BidiRange, U8T>::type,
    private as_lightweight_proxy< utf8_encode_range<BidiRange, U8T> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename utf8_encode_range_detail::super_<BidiRange, U8T>::type super_t;

public:
    explicit utf8_encode_range(BidiRange& rng) :
        super_t(rng)
    { }
};


namespace utf8_encode_range_detail {


    struct baby_make
    {
        template< class Unused, class BidiRange, class U8T = boost::uint8_t >
        struct result
        {
            typedef typename egg::by_value<U8T>::type u8_t;
            typedef utf8_encode_range<BidiRange, u8_t> const type;
        };

        template< class Result, class BidiRange, class U8T >
        Result call(BidiRange& rng, U8T)
        {
            return Result(rng);
        }

        template< class Result, class BidiRange >
        Result call(BidiRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace utf8_encode_range_detail


PSTADE_EGG_FUNCTION(make_utf8_encode_range, utf8_encode_range_detail::baby_make)
PSTADE_EGG_PIPABLE(utf8_encoded, utf8_encode_range_detail::baby_make)


} } // namespace pstade::oven


#endif
