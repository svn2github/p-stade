#ifndef PSTADE_EGG_FUSE_HPP
#define PSTADE_EGG_FUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/facilities/empty.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/baby_fuse_result.hpp"
#include "./function.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_fuse
    {
        typedef
            function< detail::baby_fuse_result<Base> >
        type; // = { { Base } };
    };


    #define PSTADE_EGG_FUSE(B) \
        { { B() } } BOOST_PP_EMPTY \
    /**/


    typedef
        generator<
            result_of_fuse< deduce<boost::mpl::_1, as_value> >::type,
            use_brace_level1
        >::type
    op_fuse;


    PSTADE_POD_CONSTANT((op_fuse), fuse) = PSTADE_EGG_GENERATOR_TYPE();


} } // namespace pstade::egg


#endif
