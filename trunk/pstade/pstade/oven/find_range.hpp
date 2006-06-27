#ifndef PSTADE_OVEN_FIND_RANGE_HPP
#define PSTADE_OVEN_FIND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/algorithm/string/find_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/egg/function.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace find_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            boost::find_iterator<
                typename boost::range_result_iterator<Range>::type
            >
        > type;
    };


} // namespace find_range_detail


template< class Range >
struct find_range :
    find_range_detail::super_<Range>::type
{
private:
    typedef typename find_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    template< class FinderT >
    find_range(Range& rng, FinderT f) :
        super_t(iter_t(rng, f), iter_t())
    { }
};


namespace find_range_detail {


    struct baby_generator
    {
        template< class Range, class FinderT >
        struct result
        {
            typedef const find_range<Range> type;
        };

        template< class Result, class Range, class FinderT >
        Result call(Range& rng, FinderT f)
        {
            return Result(rng, f);
        }
    };


} // namespace find_range_detail


PSTADE_EGG_FUNCTION(make_find_range, find_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(found, find_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::find_range, 1)


#endif
