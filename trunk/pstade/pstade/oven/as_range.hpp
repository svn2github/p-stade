#ifndef PSTADE_OVEN_AS_RANGE_HPP
#define PSTADE_OVEN_AS_RANGE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./iter_range.hpp"


namespace pstade { namespace oven {


typedef op_make_iter_range op_as_range;
PSTADE_POD_CONSTANT((op_as_range), as_range) = {{}};


} } // namespace pstade::oven


#endif
