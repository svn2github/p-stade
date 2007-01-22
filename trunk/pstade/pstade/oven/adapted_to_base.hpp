#ifndef PSTADE_OVEN_ADAPTED_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTED_TO_BASE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: 'iterator_cast' of Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'is_convertible' is too permissive?
// Meanwhile, 'iterator_cast' uses 'is_same'.
//
// Can this function be used for more generic usage?
// If it can, give it a better name?
//
// This implementation is slightly complicated than
// 'iterator_cast' in order to support a reference
// type as 'Base'. Any pitfalls?


#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/automatic.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pipable.hpp>


namespace pstade { namespace oven {


template< class Base, class Adapted > inline
Base adapted_to(Adapted& ad,
    typename enable_if<
        boost::mpl::and_<
            boost::is_convertible<Adapted&, Base>,
            boost::mpl::not_< boost::is_const<Adapted> > // seems needed.
        >
    >::type = 0)
{
    return ad;
}

template< class Base, class Adapted > inline
Base adapted_to(Adapted const& ad,
    typename enable_if< boost::is_convertible<Adapted const&, Base> >::type = 0)
{
    return ad;
}

template< class Base, class Adapted > inline
Base adapted_to(Adapted const& ad,
    typename disable_if<boost::is_convertible<Adapted const&, Base> >::type = 0)
{
    return oven::adapted_to<Base>(ad.base());
}


// Note:
// This cannot support a reference type as 'Base',
// because of the weird compiler behavior...
//

template< class To >
struct op_adapted_to
{
    typedef To result_type;

    template< class From >
    To operator()(From& from) const
    {
        return oven::adapted_to<To>(from);
    }

    template< class From >
    To operator()(From const& from) const
    {
        return oven::adapted_to<To>(from);
    }
};

PSTADE_PIPABLE(to_base, (automatic< op_adapted_to<boost::mpl::_1> >))


} } // namespace pstade::oven


#endif