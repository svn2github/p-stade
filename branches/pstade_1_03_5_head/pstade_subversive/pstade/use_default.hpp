#ifndef PSTADE_USE_DEFAULT_HPP
#define PSTADE_USE_DEFAULT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2005, 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost {

    struct use_default;

}


namespace pstade {


    template< class From, class To >
    struct use_default_to :
        boost::mpl::if_< boost::is_same<From, boost::use_default>,
            To,
            From
        >
    { };


    template< class From, class ToFun >
    struct use_default_eval_to :
        boost::mpl::eval_if< boost::is_same<From, boost::use_default>,
            ToFun,
            boost::mpl::identity<From>
        >
    { };


} // namespace pstade


#endif
