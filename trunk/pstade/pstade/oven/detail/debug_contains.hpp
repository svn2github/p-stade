#ifndef PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP
#define PSTADE_OVEN_DETAIL_DEBUG_CONTAINS_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // iterator_tag's
#include <boost/range/end.hpp>
#include <pstade/unused.hpp>
#include "../algorithm.hpp" // find
#include "../direct_range.hpp"
#include "../range_category.hpp"
#include "./debug_function.hpp"


namespace pstade { namespace oven { namespace detail {


// Note:
// A Forward Iterator conforms to (24.1.3/1) "is_same(*it1, *it2) => it1 == it2",
// so we can check the containment (am I right?).
// Also note that many Forward Iterators (counting_iterator etc.)
// cannot conform to "is_same(*it1, *it2) <= it1 == it2",
// which is a requirement of Forward Iterator, too.
//

template< class Range, class Iterator >
bool debug_contains_aux(Range& rng, Iterator const& it, std::forward_iterator_tag)
{
    if (it == boost::end(rng))
        return true;

    direct_range<Range> drng(rng);
    return oven::find(drng, it) != boost::end(drng);
}


template< class Range, class Iterator > inline
bool debug_contains_aux(Range& rng, Iterator const& it, std::input_iterator_tag)
{
    pstade::unused(rng, it);
    return true;
}


template< class Range, class Iterator > inline
bool debug_contains(Range& rng, Iterator const& it)
{
    detail::debug_function();

    typedef typename range_category<Range>::type cat_t;
    return detail::debug_contains_aux(rng, it, cat_t());
}


} } } // namespace pstade::oven::detail


#endif
