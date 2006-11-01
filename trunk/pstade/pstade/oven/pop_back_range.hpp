#ifndef PSTADE_OVEN_POP_BACK_RANGE_HPP
#define PSTADE_OVEN_POP_BACK_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'rng|applied(pop_back);' is better?
// But Haskell provides one named 'init' as primitive.


#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/range_prior.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct pop_back_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< pop_back_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    pop_back_range(Range& rng) :
        super_t(boost::begin(rng), detail::range_prior(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace pop_back_range_detail {


    struct baby_make
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef pop_back_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace pop_back_range_detail


PSTADE_EGG_FUNCTION(make_pop_back_range, pop_back_range_detail::baby_make)
PSTADE_EGG_PIPABLE(popped_back, pop_back_range_detail::baby_make)


} } // namespace pstade::oven


#endif