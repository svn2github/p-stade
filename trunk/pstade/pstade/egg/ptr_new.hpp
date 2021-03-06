#ifndef PSTADE_PTR_NEW_HPP
#define PSTADE_PTR_NEW_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include "./by_value.hpp"
#include "./compose.hpp"
#include "./construct.hpp"
#include "./new.hpp"
#include "./register_nullary_result.hpp"


namespace pstade { namespace egg {


    template<class Ptr, class Strategy = boost::use_default>
    struct X_ptr_new :
        result_of_compose<
            X_construct<Ptr, by_value>,
            X_new<typename boost::pointee<Ptr>::type, Strategy>,
            Ptr,
            Strategy
        >::type
    { };


} } // namespace pstade::egg


PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::X_ptr_new, (class)(class))


#include "./detail/suffix.hpp"
#endif
