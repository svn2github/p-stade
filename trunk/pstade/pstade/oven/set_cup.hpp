#ifndef PSTADE_OVEN_SET_CUP_HPP
#define PSTADE_OVEN_SET_CUP_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./merged.hpp"


namespace pstade { namespace oven {


namespace set_cup_detail {


    struct merge_routine :
        merge_iterator_detail::merge_routine
    {
        template< class Iterator1, class Iterator2, class Compare >
        static void after_yield(
            Iterator1& first1, Iterator1 const& last1,
            Iterator2& first2, Iterator2 const& last2,
            Compare comp)
        {
            // copy-copy phase
            if (first1 == last1) {
                ++first2;
                return;
            }
            else if (first2 == last2) {
                ++first1;
                return;
            }

            // while phase
            if (comp(*first2, *first1))
                ++first2;
            else if (comp(*first1, *first2))
                ++first1;
            else {
                ++first1;
                ++first2;
            }
        }
    };


} // namespace set_cup_detail


PSTADE_OVEN_DETAIL_MERGE_ADAPTOR(set_cup, set_cup_detail::merge_routine)


} } // namespace pstade::oven


#endif