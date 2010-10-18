#ifndef PSTADE_OVEN_ZIPPED_WITH_INDEX_HPP
#define PSTADE_OVEN_ZIPPED_WITH_INDEX_HPP
#include "./detail/prefix.hpp"

#include <pstade/result_of.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/pack.hpp>
#include <pstade/oven/zipped.hpp>
#include <pstade/oven/zipped_with.hpp>

// PStade.Oven
//
// Copyright Shunsuke Sogame, Akira Takahashi, heisseswasser 2005-2010.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// See: http://d.hatena.ne.jp/heisseswasser/20100916/1284606231

namespace pstade { namespace oven {

namespace zipped_with_index_detail {

    struct little
    {
        typedef std::size_t incrementable_t;
        typedef result_of<T_counting(incrementable_t, incrementable_t)>::type counting_range_t;
        
        template< class Myself, class Range, class BinaryFun = void>
        struct apply
        {
            typedef
                typename result_of<
                    T_pack(
                        typename iter_range_of<Range>::type,
                        typename iter_range_of<counting_range_t>::type
                    )
                >::type
            range_tuple_t;

            typedef
                typename result_of<
                    X_make_zipped_with<>(range_tuple_t, BinaryFun&)
                >::type
            type;
        };

        template< class Result, class Range, class BinaryFun >
        Result call(Range &r, BinaryFun &f) const
        {
            return pack(r, counting((incrementable_t)0, (incrementable_t)(r|distance)))|zipped_with(f);
        }

        template< class Myself, class Range >
        struct apply<Myself, Range>
        {
            typedef
                typename result_of<
                    T_pack(
                        typename iter_range_of<Range>::type,
                        typename iter_range_of<counting_range_t>::type
                    )
                >::type
            range_tuple_t;

            typedef
                typename result_of<
                    T_make_zipped(range_tuple_t)
                >::type
            type;
        };

        template<class Result, class Range>
        Result call(Range &r) const
        {
            return pack(r, counting((incrementable_t)0, (incrementable_t)(r|distance)))|zipped;
        }
    };

} // namespace zipped_with_index_detail

PSTADE_OVEN_LITTLE_TO_ADAPTOR(zipped_with_index, (zipped_with_index_detail::little))

}} // namespace pstade::oven

#endif

