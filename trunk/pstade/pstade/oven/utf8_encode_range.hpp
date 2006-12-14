#ifndef PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP
#define PSTADE_OVEN_UTF8_ENCODE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint8_t
#include <boost/regex/pending/unicode_iterator.hpp> // u32_to_u8_iterator
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace utf8_encode_range_detail {


    template<
        class Range,
        class U8T
    >
    struct super_ :
        iter_range<
            boost::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8T
            >
        >
    { };


} // namespace utf8_encode_range_detail


template<
    class Range,
    class U8T = boost::uint8_t
>
struct utf8_encode_range :
    utf8_encode_range_detail::super_<Range, U8T>::type,
    private as_lightweight_proxy< utf8_encode_range<Range, U8T> >
{
    PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef utf8_encode_range type;

private:
    typedef typename utf8_encode_range_detail::super_<Range, U8T>::type super_t;

public:
    explicit utf8_encode_range(Range& rng, unused_argument = unused_argument()) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_utf8_encode_range,
    const(utf8_encode_range< deduce_to_qualified<from_1>, deduce_to_value<from_2, boost::uint8_t> >))
PSTADE_PIPABLE(utf8_encoded, (op_make_utf8_encode_range))


} } // namespace pstade::oven


#endif
