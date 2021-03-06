#ifndef PSTADE_TO_VALUE_HPP
#define PSTADE_TO_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function_by_value.hpp>
#include <pstade/egg/object.hpp>


namespace pstade {


    namespace to_value_detail_ {


        struct baby
        {
            typedef
                egg::function_by_value<baby>
            nullary_result_type;

            template<class Result>
            Result call() const
            {
                Result result = { {} };
                return result;
            }

            template<class Myself, class A>
            struct apply
            {
                typedef A type;
            };

            template<class Result, class A>
            Result call(A a) const
            {
                return a;
            }
        };


        typedef egg::function_by_value<baby> op;


        template<class A> inline
        A operator|(A a, op)
        {
            return a;
        }


    } // namespace to_value_detail_


    typedef to_value_detail_::op op_to_value;
    PSTADE_EGG_OBJECT((op_to_value), to_value) = { {} };


} // namespace pstade



#endif
