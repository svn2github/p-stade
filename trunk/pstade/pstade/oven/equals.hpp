#ifndef PSTADE_OVEN_EQUALS_HPP
#define PSTADE_OVEN_EQUALS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: 'equals' at Boost.StringAlgorithm
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // equal
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/constant.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/functional.hpp> // equal_to
#include "./concepts.hpp"
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


namespace equals_detail {


    // Question:
    // Boost doesn't have this overload. Faster or slower?
    template< class Iterator1, class Iterator2, class BinaryPred >
    bool aux(
        Iterator1 first1, Iterator1 const& last1,
        Iterator2 first2, Iterator2 const& last2, BinaryPred& pred,
        boost::random_access_traversal_tag)
    {
        if ((last1 - first1) != (last2 - first2))
            return false;

        return std::equal(first1, last1, first2, pred);
    }


    template< class Iterator1, class Iterator2, class BinaryPred >
    bool aux(
        Iterator1 first1, Iterator1 const& last1,
        Iterator2 first2, Iterator2 const& last2, BinaryPred& pred,
        boost::single_pass_traversal_tag)
    {
        for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
            if (!pred(*first1, *first2))
                return false;
        }

        return (first2 == last2) && (first1 == last1);
    }


} // namespace equals_detail


struct op_equals
{
    typedef bool result_type;

    template< class Range1, class Range2, class BinaryPred >
    bool operator()(Range1 const& rng1, Range2 const& rng2, BinaryPred pred) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range1>));
        PSTADE_CONCEPT_ASSERT((SinglePass<Range2>));

        typedef typename boost::detail::minimum_category<
            // 'minimum_category' needs *pure*.
            typename range_pure_traversal<Range1>::type,
            typename range_pure_traversal<Range2>::type
        >::type trv_t;

        return equals_detail::aux(
            boost::begin(rng1), boost::end(rng1),
            boost::begin(rng2), boost::end(rng2), pred,
            trv_t()
        );
    }

    template< class Range1, class Range2 >
    bool operator()(Range1 const& rng1, Range2 const& rng2) const
    {
        return (*this)(rng1, rng2, equal_to);
    }
};


PSTADE_ADL_BARRIER(equals) { // for Boost

PSTADE_CONSTANT(equals, (op_equals))

} // ADL barrier


} } // namespace pstade::oven


#endif
