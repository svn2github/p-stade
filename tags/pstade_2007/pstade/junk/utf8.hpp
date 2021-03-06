#ifndef PSTADE_OVEN_UTF8_HPP
#define PSTADE_OVEN_UTF8_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class U8T = boost::uint8_t >
struct op_make_utf8_encoded :
    callable< op_make_utf8_encoded<U8T> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            boost::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8T
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        return Result(rng);
    }
};

PSTADE_CONSTANT(make_utf8_encoded, (op_make_utf8_encoded<>))
PSTADE_PIPABLE(utf8_encoded, (op_make_utf8_encoded<>))


template< class Ucs4T = boost::uint32_t >
struct op_make_utf8_decoded :
    callable< op_make_utf8_decoded<Ucs4T> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            boost::u8_to_u32_iterator<
                typename range_iterator<Range>::type,
                Ucs4T
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));
        return Result(rng);
    }
};

PSTADE_CONSTANT(make_utf8_decoded, (op_make_utf8_decoded<>))
PSTADE_PIPABLE(utf8_decoded, (op_make_utf8_decoded<>))


PSTADE_OBJECT_GENERATOR(utf8_encoder,
    (boost::utf8_output_iterator< deduce<_1, as_value> >) const)


} } // namespace pstade::oven


#endif
