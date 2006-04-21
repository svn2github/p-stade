#ifndef PSTADE_INSTANCE_HPP
#define PSTADE_INSTANCE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
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
// The ODR violation buster.


#include <boost/config.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/utility/value_init.hpp> // value_initialized
#include <pstade/comma_protect.hpp>


#define PSTADE_INSTANCE(Type, Name, MaybeArgSeq) \
    BOOST_PP_IIF(PSTADE_INSTANCE_is_seq(MaybeArgSeq), \
        PSTADE_INSTANCE_args, \
        PSTADE_INSTANCE_no_args \
    )(MaybeArgSeq, Type, Name) \
/**/


    #define PSTADE_INSTANCE_no_args(Unused, Type, Name) \
        PSTADE_INSTANCE_define_fun(Type, Name, PSTADE_INSTANCE_define_x_v(Type)) \
        \
        namespace { \
            PSTADE_INSTANCE_static \
            PSTADE_INSTANCE_comma_protect(Type)& Name = PSTADE_INSTANCE_call_instance_fun(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_args(ArgSeq, Type, Name) \
        PSTADE_INSTANCE_define_fun(Type, Name, PSTADE_INSTANCE_define_x_a(Type, ArgSeq)) \
        \
        namespace { \
            PSTADE_INSTANCE_static \
            PSTADE_INSTANCE_comma_protect(Type)& Name = PSTADE_INSTANCE_call_instance_fun(Name); \
        } \
    /**/


    #define PSTADE_INSTANCE_define_fun(Type, Name, DefineX) \
        inline \
        PSTADE_INSTANCE_comma_protect(Type)& BOOST_PP_CAT(pstade_instance_of_, Name)() \
        { \
            static DefineX \
            return x; \
        } \
    /**/


    #define PSTADE_INSTANCE_call_instance_fun(Name) \
        BOOST_PP_CAT(pstade_instance_of_, Name)() \
    /**/


    #define PSTADE_INSTANCE_is_seq \
        BOOST_PP_IS_UNARY \
    /**/


    #define PSTADE_INSTANCE_define_x_v(Type) \
        boost::value_initialized< PSTADE_INSTANCE_comma_protect(Type) > x; \
    /**/


    #define PSTADE_INSTANCE_define_x_a(Type, ArgSeq) \
        PSTADE_INSTANCE_comma_protect(Type) x(BOOST_PP_SEQ_ENUM(ArgSeq)); \
    /**/


    #define PSTADE_INSTANCE_comma_protect(Type) \
        pstade::comma_protect<void(Type)>::type \
    /**/


    // Workaround:
    //   The weird 'stdafx.h' needs 'static'.
    //
    #if !defined(BOOST_MSVC)
        #define PSTADE_INSTANCE_static
    #else
        #define PSTADE_INSTANCE_static static
    #endif


#endif
