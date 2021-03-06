#ifndef PSTADE_EGG_INTEGRAL_HPP
#define PSTADE_EGG_INTEGRAL_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/pod_constant.hpp>
#include "./ambi.hpp"
#include "./automatic.hpp"


namespace pstade { namespace egg {


    template<class To>
    struct X_integral_cast
    {
        typedef X_integral_cast function_type;
        typedef To result_type;

        template<class From>
        To operator()(From const& from) const
        {
            BOOST_MPL_ASSERT((boost::is_integral<To>));
            BOOST_MPL_ASSERT((boost::is_integral<From>));
            return boost::numeric_cast<To>(from);
        }
    };

    template<class To, class From> inline
    To integral_cast(From const& from)
    {
        return X_integral_cast<To>()(from);
    }


    namespace integral_detail {
        typedef automatic< X_integral_cast<boost::mpl::_1> >::type op;
    }

    typedef result_of_ambi0<integral_detail::op>::type T_integral;
    PSTADE_POD_CONSTANT((T_integral), integral) = PSTADE_EGG_AMBI_L PSTADE_EGG_AUTOMATIC() PSTADE_EGG_AMBI_R;


} } // namespace pstade::egg


#endif
