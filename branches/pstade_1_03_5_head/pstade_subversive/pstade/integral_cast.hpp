#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    template<class To>
    struct op_integral_cast
    {
        typedef To result_type;
        
        template<class From>
        To operator()(From const& from) const
        {
            BOOST_MPL_ASSERT((boost::is_integral<To>));
            BOOST_MPL_ASSERT((boost::is_integral<From>));
            return boost::numeric_cast<To>(from);
        }
    };


    PSTADE_SPECIFIED1(integral_cast, op_integral_cast, 1)
    PSTADE_AUXILIARY(0, to_integer, (automatic< op_integral_cast<_> >))


} // namespace pstade


#endif
