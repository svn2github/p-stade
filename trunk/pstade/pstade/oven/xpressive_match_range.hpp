#ifndef PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP
#define PSTADE_OVEN_XPRESSIVE_MATCH_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/xpressive/regex_iterator.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


namespace xpressive_match_range_detail {


    template< class BidiRange >
    struct super_
    {
        typedef boost::iterator_range<
            boost::xpressive::regex_iterator<
                // Xpressive seems not to support a mutable iterator.
                typename range_iterator_const<BidiRange>::type
            >
        > type;
    };


    using boost::xpressive::regex_constants::match_flag_type;
    using boost::xpressive::regex_constants::match_default;


} // namespace xpressive_match_range_detail


template< class BidiRange >
struct xpressive_match_range :
    xpressive_match_range_detail::super_<BidiRange>::type,
    private as_lightweight_proxy< xpressive_match_range<BidiRange> >
{
    typedef BidiRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(BidiRange, BidirectionalRangeConcept);
    typedef typename xpressive_match_range_detail::super_<BidiRange>::type super_t;
    typedef typename super_t::iterator iter_t;
    typedef typename iter_t::regex_type regex_t;

public:
    xpressive_match_range(
        BidiRange& rng,
        regex_t const& re,
        xpressive_match_range_detail::match_flag_type flag = xpressive_match_range_detail::match_default
    ) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), re, flag),
            iter_t()
        )
    { }
};


namespace xpressive_match_range_detail {


    struct baby_make
    {
        template< class Unused, class BidiRange, class Regex, class Flag = void >
        struct result
        {
            typedef xpressive_match_range<BidiRange> const type;
        };

        template< class Result, class BidiRange, class Regex >
        Result call(BidiRange& rng, Regex const& re, match_flag_type flag = match_default)
        {
            return Result(rng, re, flag);
        }
    };


} // namespace xpressive_match_range_detail


PSTADE_EGG_FUNCTION(make_xpressive_match_range, xpressive_match_range_detail::baby_make)
PSTADE_EGG_PIPABLE(xpressive_matches, xpressive_match_range_detail::baby_make)


} } // namespace pstade::oven


#endif
