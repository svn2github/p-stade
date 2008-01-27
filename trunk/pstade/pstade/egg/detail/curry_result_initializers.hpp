#ifndef PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#define PSTADE_EGG_DETAIL_CURRY_RESULT_INITIALIZERS_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/preprocessor.hpp>
#include "./bind_left1.hpp"
#include "./bind_leftx.hpp"


#define PSTADE_EGG_CURRY_L(N) PSTADE_PP_CAT3(PSTADE_EGG_CURRY, N, _L)
#define PSTADE_EGG_CURRY_R(N) PSTADE_PP_CAT3(PSTADE_EGG_CURRY, N, _R)

// PSTADE_EGG_BIND_LEFT1_L PSTADE_EGG_BIND_LEFTX_INIT , Base PSTADE_EGG_BIND_LEFT1_R
#define PSTADE_EGG_CURRY_left  PSTADE_EGG_BIND_LEFT1_L PSTADE_EGG_BIND_LEFTX_INIT ,
#define PSTADE_EGG_CURRY_right PSTADE_EGG_BIND_LEFT1_R

#define PSTADE_EGG_CURRY2_L PSTADE_EGG_CURRY_left
#define PSTADE_EGG_CURRY2_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY3_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY2_L
#define PSTADE_EGG_CURRY3_R PSTADE_EGG_CURRY2_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY4_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY3_L
#define PSTADE_EGG_CURRY4_R PSTADE_EGG_CURRY3_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY5_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY4_L
#define PSTADE_EGG_CURRY5_R PSTADE_EGG_CURRY4_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY6_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY5_L
#define PSTADE_EGG_CURRY6_R PSTADE_EGG_CURRY5_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY7_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY6_L
#define PSTADE_EGG_CURRY7_R PSTADE_EGG_CURRY6_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY8_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY7_L
#define PSTADE_EGG_CURRY8_R PSTADE_EGG_CURRY7_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY9_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY8_L
#define PSTADE_EGG_CURRY9_R PSTADE_EGG_CURRY8_R PSTADE_EGG_CURRY_right

#define PSTADE_EGG_CURRY10_L PSTADE_EGG_CURRY_left PSTADE_EGG_CURRY9_L
#define PSTADE_EGG_CURRY10_R PSTADE_EGG_CURRY9_R PSTADE_EGG_CURRY_right


// #define PSTADE_EGG_CURRY(N) BOOST_PP_CAT(PSTADE_EGG_CURRY, N)
#define PSTADE_EGG_CURRY2(F) PSTADE_EGG_CURRY2_L F PSTADE_EGG_CURRY2_R
#define PSTADE_EGG_CURRY3(F) PSTADE_EGG_CURRY3_L F PSTADE_EGG_CURRY3_R
#define PSTADE_EGG_CURRY4(F) PSTADE_EGG_CURRY4_L F PSTADE_EGG_CURRY4_R
#define PSTADE_EGG_CURRY5(F) PSTADE_EGG_CURRY5_L F PSTADE_EGG_CURRY5_R
#define PSTADE_EGG_CURRY6(F) PSTADE_EGG_CURRY6_L F PSTADE_EGG_CURRY6_R
#define PSTADE_EGG_CURRY7(F) PSTADE_EGG_CURRY7_L F PSTADE_EGG_CURRY7_R
#define PSTADE_EGG_CURRY8(F) PSTADE_EGG_CURRY8_L F PSTADE_EGG_CURRY8_R
#define PSTADE_EGG_CURRY9(F) PSTADE_EGG_CURRY9_L F PSTADE_EGG_CURRY9_R
#define PSTADE_EGG_CURRY10(F) PSTADE_EGG_CURRY10_L F PSTADE_EGG_CURRY10_R


#endif
