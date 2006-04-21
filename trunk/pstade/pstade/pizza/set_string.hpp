#ifndef PSTADE_PIZZA_SET_STRING_HPP
#define PSTADE_PIZZA_SET_STRING_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/overload.hpp>
#include <pstade/tomato/c_str.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include "./access.hpp"
#include "./detail/has_pstade_pizza_profile.hpp"


namespace pstade { namespace pizza {


namespace set_string_detail {


    struct member_function
    {
        template< class Profile > static
        void call(Profile& pr, const TCHAR *pszValueName, const TCHAR *pszValue)
        {
            access::detail_set_string(pr, pszValueName, pszValue);
        }
    };


    struct adl_customization
    {
        template< class Profile > static
        void call(Profile& pr, const TCHAR *pszValueName, const TCHAR *pszValue)
        {
            pstade_pizza_set_string(pr, pszValueName, pszValue, overload());
        }
    };


} // namespace set_string_detail


template< class Profile, class CStringizeable0, class CStringizeable1 > inline
void set_string(Profile& pr, const CStringizeable0& valueName, const CStringizeable1& value)
{
    const TCHAR *pszValueName = tomato::c_str(valueName);
    const TCHAR *pszValue = tomato::c_str(value);
    BOOST_ASSERT(diet::valid(pszValueName));
    BOOST_ASSERT(diet::valid(pszValue));


    using namespace set_string_detail;

    typedef typename
    boost::mpl::if_< detail::has_pstade_pizza_profile<Profile>,
        member_function,
        adl_customization
    >::type impl_t;

    impl_t::call(pr, pszValueName, pszValue);
}


} } // namespace pstade::pizza


#endif
