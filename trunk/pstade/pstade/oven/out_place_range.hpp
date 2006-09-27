#ifndef PSTADE_OVEN_OUT_PLACE_RANGE_HPP
#define PSTADE_OVEN_OUT_PLACE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
// See "./sort_range.hpp"


// Note:
//
// Iterators manage temporary container for BOOST_FOREACH.


#include <memory> // auto_ptr
#include <vector>
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/new.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./copy_range.hpp"
#include "./detail/concept_check.hpp"
#include "./direct_range.hpp"
#include "./indirect_range.hpp"
#include "./range_iterator.hpp"
#include "./share_range.hpp"


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310)
    // 'private' multiple inheritance of 'as_lightweight_proxy' makes VC7.1 anger.
    // I don't know why. Who knows.
    #define PSTADE_OVEN_OUT_PLACE_RANGE_WEIRD_ERROR_WITH_SORT_RANGE
#endif


namespace pstade { namespace oven {


namespace out_place_range_detail {


    template< class ForwardRange >
    struct iter_sequence
    {   
        typedef typename range_iterator<ForwardRange>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class ForwardRange >
    struct super_
    {
        typedef oven::indirect_range<
            oven::share_range<
                typename iter_sequence<ForwardRange>::type
            > const
        > type;
    };


    template< class IterSeq, class ForwardRange, class UnaryFun >
    oven::share_range<IterSeq> const
    make_share(ForwardRange& rng, UnaryFun fun)
    {
        // Note:
        // 'share_range' size never be affected by its holding sequence
        // once constructed. So, first of all, you must initialize the sequence
        // before passing it to 'share_range'.
        std::auto_ptr<IterSeq> pseq(pstade::new_<IterSeq>());
        *pseq = oven::copy_range<IterSeq>(rng|directed);

        // Question:
        // What should be passed to 'fun'?
        fun(*pseq);        

        return share_range<IterSeq>(pseq.release());
    }


} // namespace out_place_range_detail


template<
    class ForwardRange,
    class UnaryFun = unused_fun
>
struct out_place_range :
    out_place_range_detail::super_<ForwardRange>::type,
#if !defined(PSTADE_OVEN_OUT_PLACE_RANGE_WEIRD_ERROR_WITH_SORT_RANGE)
    private
#endif
    as_lightweight_proxy< out_place_range<ForwardRange, UnaryFun> >
{
    typedef ForwardRange pstade_oven_range_base_type;
    typedef UnaryFun function_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename out_place_range_detail::super_<ForwardRange>::type super_t;
    typedef typename out_place_range_detail::iter_sequence<ForwardRange>::type seq_t;

public:
    explicit out_place_range(ForwardRange& rng, UnaryFun const& fun = unused) :
        super_t(out_place_range_detail::make_share<seq_t>(rng, fun))
    { }
};


namespace out_place_range_detail {


    struct baby_make
    {
        template< class Unused, class ForwardRange, class UnaryFun = unused_fun >
        struct apply
        {
            typedef typename pass_by_value<UnaryFun>::type fun_t;
            typedef out_place_range<ForwardRange, fun_t> const type;
        };

        template< class Result, class ForwardRange, class UnaryFun >
        Result call(ForwardRange& rng, UnaryFun& fun)
        {
            return Result(rng, fun);
        }

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace out_place_range_detail


PSTADE_EGG_FUNCTION(make_out_place_range, out_place_range_detail::baby_make)
PSTADE_EGG_PIPABLE(out_placed, out_place_range_detail::baby_make)


} } // namespace pstade::oven


#endif
