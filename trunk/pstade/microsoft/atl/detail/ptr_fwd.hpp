#ifndef BOOST_MICROSOFT_ATL_DETAIL_PTR_FWD_HPP
#define BOOST_MICROSOFT_ATL_DETAIL_PTR_FWD_HPP


// Boost.Microsoft
//
// Copyright 2006 Shunsuke Sogame.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <guiddef.h> // IID


namespace ATL {


template< class E >
class CAutoPtr;


template< class T, const IID *piid >
class CComQIPtr;


template< class T >
class CAdapt;


} // nemspace ATL


#endif
