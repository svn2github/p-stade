#ifndef PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./tab_unexpand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_unexpand_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            tab_unexpand_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace tab_expand_range_detail


template< class Range >
struct tab_unexpand_range :
    tab_unexpand_range_detail::super_<Range>::type,
    private as_lightweight_proxy< tab_unexpand_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef tab_unexpand_range type;

private:
    typedef typename tab_unexpand_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    tab_unexpand_range(Range& rng, int tabsize) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng), tabsize),
            iter_t(boost::end(rng),   boost::end(rng), tabsize)
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_tab_unexpand_range,
    const(tab_unexpand_range< deduce_to_qualified<from_1> >))
PSTADE_PIPABLE(tab_unexpanded, (op_make_tab_unexpand_range))


} } // namespace pstade::oven


#endif
