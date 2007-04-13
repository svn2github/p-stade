#ifndef PSTADE_OVEN_SORTED_HPP
#define PSTADE_OVEN_SORTED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// Because this adaptor is *expensive* enough
// to effect on your software design sooner or later.
// On the other hand, when you can accept the big time-and-space,
// this may be still useful. So I don't remove...


// References:
//
// [1] Gabhan Berry, C++ View Objects, Dr.Dobb's Portal, 2006.
//     http://www.ddj.com/dept/cpp/196513737


#include <algorithm> // sort
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./outplaced.hpp"


namespace pstade { namespace oven {


namespace sorted_detail {


    template< class Compare >
    struct op_sort
    {
        explicit op_sort(Compare comp) :
            m_comp(comp)
        { }

        template< class Range >
        void operator()(Range& its) const
        {
            std::sort(boost::begin(its), boost::end(its), boost::make_indirect_fun(m_comp));
        }

    private:
        Compare m_comp;
    };


} // namespace sorted_detail


struct op_make_sorted :
    callable<op_make_sorted>
{
    template< class Myself, class Range, class Compare = op_less const >
    struct apply
    {
        typedef
            sorted_detail::op_sort<
                typename pass_by_value<Compare>::type
            >
        fun_t;

        typedef typename
            boost::result_of<
                op_make_outplaced(Range&, fun_t)
            >::type
        type;
    };

    template< class Result, class Range, class Compare >
    Result call(Range& rng, Compare& comp) const
    {
        PSTADE_CONCEPT_ASSERT((Forward<Range>));

        typedef typename apply<void, Range, Compare>::fun_t fun_t;
        return make_outplaced(rng, fun_t(comp));
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return (*this)(rng, less);
    }
};


PSTADE_CONSTANT(make_sorted, (op_make_sorted))
PSTADE_PIPABLE(sorted, (op_make_sorted))


} } // namespace pstade::oven


#endif
