#ifndef PSTADE_OVEN_TRANSFORMED_HPP
#define PSTADE_OVEN_TRANSFORMED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Consider the following simple functor.
//
// struct id
// {
//     typedef int const& result_type;
//     result_type operator()(int const& x) const
//     { return x; }
// };
//
// A transformed range whose 'reference' is 'int'(non-reference)
// cannot work with this functor because of dangling reference.
// A transformed range's 'reference' type is sometimes
// orthogonal to functor's 'result_type'.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./concepts.hpp"
#include "./identities.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template<
    class Reference = boost::use_default,
    class Value     = boost::use_default
>
struct op_make_transformed :
    callable< op_make_transformed<Reference, Value> >
{
    template< class Myself, class Range, class UnaryFun >
    struct apply
    {
        typedef typename range_iterator<Range>::type base_iter_t;
        typedef typename pass_by_value<UnaryFun>::type fun_t;

        typedef typename
            boost::iterator_reference<base_iter_t>::type
        base_ref_t;

        typedef typename
            use_default_eval_to<
                Reference,
                boost::result_of<fun_t(base_ref_t)>
            >::type
        ref_t;

        typedef
            boost::transform_iterator<
                fun_t, base_iter_t, ref_t, Value
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        rng_t;

        // Recompute IteratorCategory using 'identities'.
        // 'fun' may resurrect lvalue-ness of the base range,
        // then a RandomAccess*Input* Iterator turns into the RandomAccess.
        // e.g. applying 'at' to a tuple of reference.
        typedef typename
            boost::result_of<
                op_make_identities(rng_t)
            >::type
        type;
    };

    template< class Result, class Range, class UnaryFun >
    Result call(Range& rng, UnaryFun& fun) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef apply<void, Range, UnaryFun> apply_t;
        return make_identities(
            typename apply_t::rng_t(
                typename apply_t::iter_t(boost::begin(rng), fun),
                typename apply_t::iter_t(boost::end(rng),   fun)
            )
        );
    }
};


PSTADE_CONSTANT(make_transformed, (op_make_transformed<>))
PSTADE_PIPABLE(transformed, (op_make_transformed<>))


} } // namespace pstade::oven


#endif
