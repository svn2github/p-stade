#ifndef PSTADE_OVEN_TAKE_RANGE_HPP
#define PSTADE_OVEN_TAKE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./distance.hpp"
#include "./range_difference.hpp"
#include "./range_traversal.hpp"
#include "./take_while_range.hpp"


namespace pstade { namespace oven {


namespace take_range_detail {


    template< class Difference >
    struct count_down
    {
        explicit count_down(Difference d) :
            m_d(d)
        { }
    
        template< class T >
        bool operator()(T const&)
        {
            return m_d--
                != 0; // suppress a VC++ warning.
        }

    private:
        Difference m_d;
    };


    template< class Range >
    struct super_ :
        boost::mpl::eval_if<
            boost::is_convertible<
                typename range_traversal<Range>::type,
                boost::forward_traversal_tag
            >,
            sub_range_base<Range>,
            boost::mpl::identity<
                take_while_range<
                    Range, count_down<typename range_difference<Range>::type>
                >
            >
        >
    { };


    template< class Super, class Range, class Difference > inline
    Super make(Range& rng, Difference d, boost::forward_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));
        BOOST_ASSERT(0 <= d && d <= oven::distance(rng));

        return Super(
            boost::begin(rng),
            detail::next(boost::begin(rng), d)
        );
    }

    template< class Super, class Range, class Difference > inline
    Super make(Range& rng, Difference d, boost::single_pass_traversal_tag)
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename range_difference<Range>::type diff_t;
        return Super(rng, count_down<diff_t>(d));
    }


} // namespace take_range_detail


template< class Range >
struct take_range :
    take_range_detail::super_<Range>::type,
    private as_lightweight_proxy< take_range<Range> >
{
private:
    typedef typename take_range_detail::super_<Range>::type super_t;
    typedef typename range_traversal<Range>::type trv_t;

public:
    template< class Difference >
    take_range(Range& rng, Difference d) :
        super_t(take_range_detail::make<super_t>(rng, d, trv_t()))
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace take_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Difference >
        struct apply
        {
            typedef take_range<Range> const type;
        };

        template< class Result, class Range, class Difference >
        Result call(Range& rng, Difference d) const
        {
            return Result(rng, d);
        }
    };


} // namespace take_range_detail


PSTADE_EGG_FUNCTION(make_take_range, take_range_detail::baby_make)
PSTADE_PIPABLE(taken, make_take_range_fun)


} } // namespace pstade::oven


#endif
