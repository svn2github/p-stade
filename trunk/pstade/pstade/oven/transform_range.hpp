#ifndef PSTADE_OVEN_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_TRANSFORM_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace transform_range_detail {


    template< class Iterator, class UnaryFun >
    struct default_reference
    {
        typedef typename boost::iterator_reference<Iterator>::type ref_t;
        typedef typename boost::result_of<UnaryFun(ref_t)>::type type;
    };


    template<
        class Range, class UnaryFun,
        class Reference, class Value
    >
    struct super_
    {
        typedef typename range_iterator<Range>::type iter_t;

        // Note:
        // Boost.Iterator doesn't use 'result_of'.
        // 'result_of' seems to have many problems
        // even under modern compilers. But we must go!
        typedef typename boost::mpl::eval_if<
            boost::is_same<Reference, boost::use_default>,
            default_reference<iter_t, UnaryFun>,
            boost::mpl::identity<Reference>
        >::type ref_t;

        typedef boost::iterator_range<
            boost::transform_iterator<
                UnaryFun, iter_t, ref_t, Value
            >
        > type;
    };

} // namespace transform_range_detail


template<
    class Range, class UnaryFun,
    class Reference = boost::use_default, class Value = boost::use_default
>
struct transform_range :
    transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type,
    private as_lightweight_proxy< transform_range<Range, UnaryFun, Reference, Value> >
{
    typedef Range pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename transform_range_detail::super_<Range, UnaryFun, Reference, Value>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    transform_range(Range& rng, UnaryFun const& fun) :
        super_t(
            iter_t(boost::begin(rng), fun),
            iter_t(boost::end(rng), fun)
        )
    { }
};


namespace transform_range_detail {


    struct baby_make
    {
        template< class Unused, class Range, class UnaryFun >
        struct result
        {
            typedef typename pass_by_value<UnaryFun>::type fun_t;
            typedef transform_range<Range, fun_t> const type;
        };

        template< class Result, class Range, class UnaryFun >
        Result call(Range& rng, UnaryFun& fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace transform_range_detail


PSTADE_EGG_FUNCTION(make_transform_range, transform_range_detail::baby_make)
PSTADE_EGG_PIPABLE(transformed, transform_range_detail::baby_make)


} } // namespace pstade::oven


#endif
