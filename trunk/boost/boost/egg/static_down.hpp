#ifndef BOOST_EGG_STATIC_DOWN_HPP
#define BOOST_EGG_STATIC_DOWN_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./automatic.hpp"
#include "./static_downcast.hpp"


namespace pstade { namespace egg {


    typedef
        result_of_ambi0<
            automatic_ref< X_static_downcast<boost::mpl::_> >::type
        >::type
    T_static_down;

    PSTADE_POD_CONSTANT((T_static_down), static_down)
        = BOOST_EGG_AMBI_L BOOST_EGG_AUTOMATIC_REF BOOST_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
