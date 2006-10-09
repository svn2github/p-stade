#ifndef PSTADE_OVEN_REPEAT_RANGE_HPP
#define PSTADE_OVEN_REPEAT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./range_iterator.hpp"
#include "./repeat_iterator.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace repeat_range_detail {


    template<
        class Range,
        class Size
    >
    struct super_
    {
        typedef boost::iterator_range<
            repeat_iterator<
                typename range_iterator<Range>::type,
                Size
            >
        > type;
    };


} // namespace repeat_range_detail


template<
    class Range,
    class Size = std::size_t
>
struct repeat_range :
    repeat_range_detail::super_<Range, Size>::type,
    private as_lightweight_proxy< repeat_range<Range, Size> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename repeat_range_detail::super_<Range, Size>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    repeat_range(Range& rng, Size sz) :
        super_t(
            iter_t(boost::begin(rng), 0,  boost::begin(rng), boost::end(rng)),
            iter_t(boost::begin(rng), sz, boost::begin(rng), boost::end(rng))
        )
    { }

    typename sub_range_result<Range>::type source() const
    {
        return boost::make_iterator_range(this->begin().sbegin(), this->begin().send());
    }

    typedef Range pstade_oven_range_base_type;
};


namespace repeat_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Size >
        struct apply
        {
            typedef typename pass_by_value<Size>::type sz_t;
            typedef repeat_range<Range, sz_t> const type;
        };

        template< class Result, class Range, class Size >
        Result call(Range& rng, Size sz)
        {
            return Result(rng, sz);
        }
    };


} // namespace repeat_range_detail


PSTADE_EGG_FUNCTION(make_repeat_range, repeat_range_detail::baby_make)
PSTADE_EGG_PIPABLE(repeated, repeat_range_detail::baby_make)


} } // namespace pstade::oven


#endif
