#ifndef PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_iterator.hpp"
#include "./tab_unexpand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_unexpand_range_detail {


    template< class ForwardRange >
    struct super_
    {
        typedef boost::iterator_range<
            tab_unexpand_iterator<
                typename range_iterator<ForwardRange>::type
            >
        > type;
    };


} // namespace tab_expand_range_detail


template< class ForwardRange >
struct tab_unexpand_range :
    tab_unexpand_range_detail::super_<ForwardRange>::type,
    private lightweight_proxy< tab_unexpand_range<ForwardRange> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename tab_unexpand_range_detail::super_<ForwardRange>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    tab_unexpand_range(ForwardRange& rng, int tabsize) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), tabsize),
            iter_t(boost::end(rng), boost::end(rng), tabsize)
        )
    { }
};


namespace tab_unexpand_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class TabSizeT >
        struct result
        {
            typedef tab_unexpand_range<ForwardRange> const type;
        };

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng, int tabsize)
        {
            return Result(rng, tabsize);
        }
    };


} // namespace tab_unexpand_range_detail


PSTADE_EGG_FUNCTION(make_tab_unexpand_range, tab_unexpand_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(tab_unexpanded, tab_unexpand_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
