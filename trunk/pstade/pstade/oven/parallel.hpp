#ifndef PSTADE_OVEN_PARALLEL_HPP
#define PSTADE_OVEN_PARALLEL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2104.pdf
//
// This cheap implementation is just out of curiosity.


#include <boost/range/empty.hpp>
#include <boost/thread/thread.hpp>
#include <pstade/egg/function.hpp>
#include "./algorithm.hpp" // for_each
#include "./any_range.hpp"
#include "./distance.hpp"
#include "./drop_range.hpp"
#include "./range_difference.hpp"
#include "./range_reference.hpp"
#include "./range_traversal.hpp"
#include "./range_value.hpp"
#include "./take_range.hpp"


namespace pstade { namespace oven {


namespace parallel_detail {


    template< class AnyRange, class UnaryFun, class Difference >
    struct for_each_fun
    {
        template< class Range >
        for_each_fun(Range& rng, UnaryFun& fun, Difference grain) :
            m_rng(rng), m_fun(fun), m_grain(grain)
        { }

        void operator()() const
        {
            if (boost::empty(m_rng))
                return;

            Difference dist = oven::distance(m_rng);

            if (dist <= m_grain) {
                oven::for_each(m_rng, m_fun);
                return;
            }

            boost::thread thrdL(for_each_fun(m_rng|taken(dist/2),   m_fun, m_grain));
            boost::thread thrdR(for_each_fun(m_rng|dropped(dist/2), m_fun, m_grain));
            thrdR.join();
            thrdL.join();
        }

    private:
        AnyRange m_rng;
        UnaryFun m_fun; // must be copied before creating threads.
        Difference m_grain;
    };

    struct baby_for_each
    {
        template< class Myself, class Range, class UnaryFun, class Difference = void >
        struct apply
        {
            typedef void type;
        };

        template< class Result, class Range, class UnaryFun, class Difference >
        Result call(Range& rng, UnaryFun& fun, Difference grain)
        {
            typedef typename range_difference<Range>::type diff_t;

            // Range type must be erased to avoid infinite recursion
            // of 'for_each_fun' template-instantiation.
            typedef
                any_range<
                    typename range_value<Range>::type,
                    typename range_traversal<Range>::type,
                    typename range_reference<Range>::type,
                    diff_t
                >
            any_range_t;

            for_each_fun<any_range_t, UnaryFun, diff_t>(rng, fun, grain)();
        }
    };


} // namespace parallel_detail


PSTADE_EGG_FUNCTION(parallel_for_each, parallel_detail::baby_for_each)


} } // namespace pstade::oven


#endif
