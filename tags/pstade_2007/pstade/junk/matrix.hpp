#ifndef PSTADE_OVEN_MATRIX_HPP
#define PSTADE_OVEN_MATRIX_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


#include <boost/assert.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/result_of.hpp>
#include <pstade/unused.hpp>
#include "../concepts.hpp"
#include "../counting.hpp"
#include "../distance.hpp"
#include "../iter_range.hpp"
#include "../range_difference.hpp"
#include "../sliced.hpp"
#include "../transformed.hpp"
#include "../window.hpp"


namespace pstade { namespace oven {


namespace rows_detail {


    template< class Range, class Difference >
    struct to_row
    {
        // Hold the base range by value for copying to outer scope.
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        typedef typename
            result_of<
                op_make_window(rng_t const&, Difference, Difference)
            >::type
        result_type;

        result_type operator()(Difference i) const
        {
            return make_window(m_rng, i*m_d2, (i+1)*m_d2);
        }

        to_row()
        { }

        to_row(Range& rng, Difference d2) :
            m_rng(rng), m_d2(d2)
        { }

    private:
        rng_t m_rng;
        Difference m_d2;
    };


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            result_of<
                op_make_transformed(
                    typename result_of<op_counting(int, diff_t&)>::type,
                    to_row<Range, diff_t>
                )
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t d1, diff_t d2) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(distance(rng) == d1*d2);

            return make_transformed(
                counting(0, d1),
                to_row<Range, diff_t>(rng, d2)
            );
        }
    };


} // namespace rows_detail


PSTADE_FUNCTION(make_rows, (rows_detail::baby<_>))
PSTADE_PIPABLE(rows, (op_make_rows))


namespace columns_detail {


    template< class Range, class Difference >
    struct to_column
    {
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        typedef typename
            result_of<
                op_make_sliced(rng_t const&, Difference&, Difference const&)
            >::type
        result_type;

        result_type operator()(Difference j) const
        {
            return make_sliced(m_rng, j, m_d2);
        }

        to_column()
        { }

        to_column(Range& rng, Difference d2) :
            m_rng(rng), m_d2(d2)
        { }

    private:
        rng_t m_rng;
        Difference m_d2;
    };


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            result_of<
                op_make_transformed(
                    typename result_of<op_counting(int, diff_t&)>::type,
                    to_column<Range, diff_t>
                )
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t d1, diff_t d2) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(distance(rng) == d1*d2);
            unused(d1);

            return make_transformed(
                counting(0, d2),
                to_column<Range, diff_t>(rng, d2)
            );
        }
    };


} // namespace columns_detail


PSTADE_FUNCTION(make_columns, (columns_detail::baby<_>))
PSTADE_PIPABLE(columns, (op_make_columns))


namespace matrix3_detail {


    template< class Range, class Difference >
    struct to_rows
    {
        typedef typename
            iter_range_of<Range>::type
        rng_t;

        typedef typename
            result_of<
                op_make_rows(
                    typename result_of<op_make_window(rng_t const&, Difference, Difference)>::type,
                    Difference&, Difference&
                )
            >::type
        result_type;

        result_type operator()(Difference i) const
        {
            return make_rows(
                make_window(m_rng, i*m_d2*m_d3, (i+1)*m_d2*m_d3),
                m_d2, m_d3
            );
        }

        to_rows()
        { }

        to_rows(Range& rng, Difference d2, Difference d3) :
            m_rng(rng), m_d2(d2), m_d3(d3)
        { }

    private:
        rng_t m_rng;
        Difference m_d2, m_d3;
    };


    template< class Range >
    struct baby
    {
        typedef typename
            range_difference<Range>::type
        diff_t;

        typedef typename
            result_of<
                op_make_transformed(
                typename result_of<op_counting(int, diff_t&)>::type,
                    to_rows<Range, diff_t>
                )
            >::type
        result_type;

        result_type operator()(Range& rng, diff_t d1, diff_t d2, diff_t d3) const
        {
            PSTADE_CONCEPT_ASSERT((RandomAccess<Range>));
            BOOST_ASSERT(distance(rng) == d1*d2*d3);

            return make_transformed(
                counting(0, d1),
                to_rows<Range, diff_t>(rng, d2, d3)
            );
        }
    };


} // namespace matrix3_detail


PSTADE_FUNCTION(make_matrix3, (matrix3_detail::baby<_>))
PSTADE_PIPABLE(matrix3, (op_make_matrix3))


struct op_make_matrix :
    callable<op_make_matrix>
{
    template< class Myself, class Range, class D1, class D2, class D3 = void, class D4 = void >
    struct apply
    { };

    template< class Myself, class Range, class D1, class D2 >
    struct apply<Myself, Range, D1, D2> :
        result_of<op_make_rows(Range&, D1&, D2&)>
    { };

    template< class Result, class Range, class D1, class D2 >
    Result call(Range& rng, D1& d1, D2& d2) const
    {
        return make_rows(rng, d1, d2);
    }

    template< class Myself, class Range, class D1, class D2, class D3 >
    struct apply<Myself, Range, D1, D2, D3> :
        result_of<op_make_matrix3(Range&, D1&, D2&, D3&)>
    { };

    template< class Result, class Range, class D1, class D2, class D3 >
    Result call(Range& rng, D1& d1, D2& d2, D3& d3) const
    {
        return make_matrix3(rng, d1, d2, d3);
    }
};


PSTADE_CONSTANT(make_matrix, (op_make_matrix))
PSTADE_PIPABLE(matrix, (op_make_matrix))


} } // namespace pstade::oven


#endif
