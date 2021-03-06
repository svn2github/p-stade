#ifndef PSTADE_INSTANCE_HPP
#define PSTADE_INSTANCE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/sequence/detail/instance.hpp>
//
// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Defines the object which is shared by all the translation units.


// Usage:
//
// PSTADE_INSTANCE((int), i, value) // value-initialize
// PSTADE_INSTANCE((string), s, ("hello"))
//
// Precondition:
// A program 'Type x(args); int main() { }' is well-defined.
// If the constructor of 'Type' accesses another translation unit object,
// it results in undefined-behavior because of the famous initialization order issue.


// Reason why 'ValueOrArgSeq' is checked:
//
// Assume you typo 'PSTADE_INSTANCE((bool), b, true)'
// instead of 'PSTADE_INSTANCE((bool), b, (true))'.
// 'b' is value-initialized, thus 'b' becomes 'false'.


// Note:
//
// You can prefer
//     PSTADE_CONSTANT(O1, (T))
//     PSTADE_CONSTANT(O2, (T)) // is_same(O1, O2) == true.
// to
//     PSTADE_INSTANCE((T) const, O1, value)
//     PSTADE_INSTANCE((T) const, O2, value) // is_same(O1, O2) == false.
// , because the const default-constructed object can be the same.


#include <boost/config.hpp> // BOOST_MSVC
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/utility/value_init.hpp> // value_initialized
#include <pstade/unparenthesize.hpp>


#define PSTADE_INSTANCE(Type, Object, ValueOrArgSeq) \
    BOOST_PP_ASSERT(PSTADE_INSTANCE_is_valid(ValueOrArgSeq)) \
    BOOST_PP_IIF( BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
        PSTADE_INSTANCE_args, \
        PSTADE_INSTANCE_no_args \
    )(PSTADE_UNPARENTHESIZE(Type), Object, ValueOrArgSeq) \
/**/


    #define PSTADE_INSTANCE_is_valid(ValueOrArgSeq) \
        BOOST_PP_IIF( BOOST_MPL_PP_IS_SEQ(ValueOrArgSeq), \
            1 BOOST_PP_TUPLE_EAT(2), \
            BOOST_MPL_PP_TOKEN_EQUAL \
        )(ValueOrArgSeq, value) \
    /**/


    #if !defined(BOOST_MPL_PP_TOKEN_EQUAL_value)
        #define BOOST_MPL_PP_TOKEN_EQUAL_value(A) \
            A \
        /**/
    #endif


    #define PSTADE_INSTANCE_no_args(Type, Object, _) \
        PSTADE_INSTANCE_define_box(Type, Object, PSTADE_INSTANCE_define_v(Type)) \
        namespace { \
            PSTADE_INSTANCE_static \
            Type& Object = PSTADE_INSTANCE_OF(Object); \
        } \
    /**/


    #define PSTADE_INSTANCE_args(Type, Object, ArgSeq) \
        PSTADE_INSTANCE_define_box(Type, Object, PSTADE_INSTANCE_define_a(Type, ArgSeq)) \
        namespace { \
            PSTADE_INSTANCE_static \
            Type& Object = PSTADE_INSTANCE_OF(Object); \
        } \
    /**/


    // Workaround:
    // The weird 'stdafx.h' needs 'static'.
    #if !defined(BOOST_MSVC)
        #define PSTADE_INSTANCE_static
    #else
        #define PSTADE_INSTANCE_static static
    #endif


    #define PSTADE_INSTANCE_box_name(Object) \
        BOOST_PP_CAT(pstade_instance_of_, Object) \
    /**/


    #define PSTADE_INSTANCE_define_box(Type, Object, DefineInstance) \
        inline \
        Type& PSTADE_INSTANCE_box_name(Object)() \
        { \
            static DefineInstance \
            return instance; \
        } \
    /**/


// Workaround:
// GCC dynamic-initialization sometimes needs a function call syntax.
#define PSTADE_INSTANCE_OF(Object) \
    PSTADE_INSTANCE_box_name(Object)() \
/**/


    #define PSTADE_INSTANCE_define_v(Type) \
        ::boost::value_initialized< Type > instance; \
    /**/


    #define PSTADE_INSTANCE_define_a(Type, ArgSeq) \
        Type instance(BOOST_PP_SEQ_ENUM(ArgSeq)); \
    /**/


#endif
