#ifndef PSTADE_OVEN_PARALLEL_HPP
#define PSTADE_OVEN_PARALLEL_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// References:
//
// [1] Arch D. Robison, A Proposal to Add Parallel Iteration to the Standard Library, 2006.
//     http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2104.pdf


#include <algorithm> // for_each
#include <boost/mpl/int.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/thread/thread.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include "./concepts.hpp"
#include "./distance.hpp"
#include "./dropped.hpp"
#include "./iter_range.hpp"
#include "./range_difference.hpp"


namespace pstade { namespace oven {


namespace parallel_detail {


    template< class IterRange, class UnaryFun, class Difference >
    struct for_each_
    {
        void operator()()
        {
            if (boost::empty(m_rng))
                return;

            Difference dist = distance(m_rng);

            if (dist <= m_grain) {
                std::for_each(boost::begin(m_rng), boost::end(m_rng), m_fun);
                return;
            }

            // Type must be reduced to 'IterRange',
            // otherwise the template instantiation recursion never stops.
            // Thus, 'split_at' is useless here.
            IterRange second_rng = make_dropped(m_rng, dist/2);
            IterRange first_rng(boost::begin(m_rng), boost::begin(second_rng));

            boost::thread thrdL(for_each_(first_rng,  m_fun, m_grain));
            boost::thread thrdR(for_each_(second_rng, m_fun, m_grain));

            thrdL.join();
            thrdR.join();
        }

        template< class Range >
        for_each_(Range& rng, UnaryFun fun, Difference grain) :
            m_rng(rng), m_fun(fun), m_grain(grain)
        { }

    private:
        IterRange  m_rng;
        UnaryFun   m_fun;
        Difference m_grain;
    };


} // namespace parallel_detail


struct op_parallel_for_each :
    callable<op_parallel_for_each>
{
    template< class Myself, class Range, class UnaryFun, class Difference = void >
    struct apply
    {
        typedef void type;
    };

    template< class Result, class Range, class UnaryFun, class Difference >
    void call(Range& rng, UnaryFun fun, Difference grain) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename range_difference<Range>::type diff_t;
        // Range type must be "erased" to avoid infinite recursion
        // of 'for_each_' template-instantiation.
        typedef typename iter_range_of<Range>::type base_t;

        parallel_detail::for_each_<base_t, UnaryFun, diff_t>(rng, fun, grain)();
    }
};


PSTADE_CONSTANT(parallel_for_each, (op_parallel_for_each))


} } // namespace pstade::oven


#endif
