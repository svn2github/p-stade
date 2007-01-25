#ifndef PSTADE_OVEN_RANGE_CONSTANTABLE_HPP
#define PSTADE_OVEN_RANGE_CONSTANTABLE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Resurrects the constant-ness of 'const_iterator'
// in the range whose 'const_iterator' is mutable.
// See 'array_range' for the usage.


#include <boost/mpl/empty_base.hpp>
#include "./detail/config.hpp" // PSTADE_OVEN_BOOST_RANGE_BEGIN/END


namespace pstade { namespace oven {


template<
    class T,
    class ConstantIter,
    class Base = boost::mpl::empty_base
>
struct range_constantable :
    Base
{
    // Note:
    // You must define this in 'T' in order to avoid ambiguity.
    // It is of little use to pass a range to 'Base',
    // because 'Base' constructors become unavailable.
    //
    // typedef ConstantIter const_iterator;

    // Eat const-qualified range
    // before member functions are looked up.
    friend
    ConstantIter PSTADE_OVEN_BOOST_RANGE_BEGIN(T const& x)
    {
        return x.begin();
    }

    friend
    ConstantIter PSTADE_OVEN_BOOST_RANGE_END(T const& x)
    {
        return x.end();
    }
};


} } // namespace pstade::oven


#endif
