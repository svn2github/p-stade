#ifndef PSTADE_SAUSAGE_DETAIL_REF_TO_PTR_HPP
#define PSTADE_SAUSAGE_DETAIL_REF_TO_PTR_HPP


// PStade.Sausage
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/remove_reference.hpp>


namespace pstade { namespace sausage { namespace detail {


template< class T >
struct ref_to_ptr :
    boost::add_pointer<
        typename boost::remove_reference<T>::type
    >
{ };


} } } // namespace pstade::sausage::detail


#endif
