#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./aggregate1.hpp"
#include "./function.hpp"
#include "./fuse_result.hpp"
#include "./generator.hpp"


namespace pstade { namespace egg {


    typedef
        function<
            generator<
                function< fuse_result< deduce<boost::mpl::_1, deducers::as_value> > >,
                aggregate1
            >
        >
    op_fuse;


    PSTADE_POD_CONSTANT(fuse, (op_fuse))


} } // namespace pstade::egg


#endif
