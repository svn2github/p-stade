#ifndef PSTADE_OVEN_OUTPLACED_HPP
#define PSTADE_OVEN_OUTPLACED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Gabhan Berry, C++ View Objects, Dr.Dobb's Portal, 2006.
//     http://www.ddj.com/dept/cpp/196513737


#include <vector>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./outdirected.hpp"
#include "./range_iterator.hpp"
#include "./shared.hpp"


namespace pstade { namespace oven {


namespace outplaced_detail {


    template< class Range >
    struct iter_sequence
    {   
        typedef
            std::vector<
                typename range_iterator<Range>::type
            >
        type;
    };


    template< class Range >
    struct baby
    {
        typedef typename
            iter_sequence<Range>::type
        iter_seq_t;

        typedef typename
            boost::result_of<
                op_make_shared(iter_seq_t *)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            PSTADE_CONCEPT_ASSERT((Forward<Range>));
            typename boost::result_of<op_make_outdirected(Range&)>::type its = make_outdirected(rng);
            return make_shared( new iter_seq_t(boost::begin(its), boost::end(its)) );
        }
    };


} // namespace outplaced_detail


PSTADE_FUNCTION(make_outplaced, (outplaced_detail::baby<_>))
PSTADE_PIPABLE(outplaced, (op_make_outplaced))


} } // namespace pstade::oven


#endif
