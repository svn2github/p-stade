#ifndef PSTADE_POD_ASSERT_HPP
#define PSTADE_POD_ASSERT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// clearly imperfect...
// FWIW, msvc is_pod<> doesn't correctly work at all.


#include <boost/preprocessor/cat.hpp>
#include <pstade/fake.hpp>
#include <pstade/pp_line.hpp>


#define PSTADE_POD_ASSERT(T) \
    struct BOOST_PP_CAT(pod_assertion_in_line_, PSTADE_PP_LINE()) \
    { \
        PSTADE_POD_ASSERT_aux(T) \
    } \
/**/


#define PSTADE_POD_ASSERT_OF(T, O) \
    struct BOOST_PP_CAT(pod_assertion_of_, O) \
    { \
        PSTADE_POD_ASSERT_aux(T) \
    } \
/**/


    #define PSTADE_POD_ASSERT_aux(T) \
        PSTADE_POD_ASSERTION_FAILURE failed() \
        { \
            return pstade::pod_assert_detail::must_be_pod(pstade::pod_assert_detail::make<void T>::value()); \
        } \
    /**/


struct PSTADE_POD_ASSERTION_FAILURE { };


namespace pstade { namespace pod_assert_detail {


    // Some compilers can warn if non-POD passed through ellipsis. 
    inline PSTADE_POD_ASSERTION_FAILURE must_be_pod(...)
    {
        return PSTADE_POD_ASSERTION_FAILURE();
    }


    template<class Sig>
    struct make;

    template<class T>
    struct make<void(T)>
    {
        static T value()
        {
            return fake<T>();
        }
    };


} } // namespace pstade::pod_assert_detail


#endif
