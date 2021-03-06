#ifndef PSTADE_OVEN_ADAPTED_TO_BASE_HPP
#define PSTADE_OVEN_ADAPTED_TO_BASE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'is_convertible' is over-optimistic?
// Meanwhile, 'iterator_cast' uses 'is_same'.
//
// Can this function be used for more generic usage?
// If it can, give it a better name?
//
// This implementation is slightly complicated than
// 'iterator_cast' in order to support a reference
// type as 'Base'. Any pitfalls?


// References:
//
// [1] Eric Niebler, iterator_cast, Boost.RangeEx, 2004.
//     http://www.boost-consulting.com/vault/index.php?directory=Algorithms


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/is_const.hpp>
#include <pstade/automatic.hpp>
#include <pstade/auxiliary.hpp>
#include <pstade/callable.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/specified.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Base >
struct op_adapted_to
{
    typedef Base result_type;

    template< class Adapted >
    Base operator()(Adapted& ad,
        typename enable_if<
#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // for weird VC7.1
            boost::mpl::and_<
                is_convertible<Adapted&, Base>,
                boost::mpl::not_< boost::is_const<Adapted> >
            >
#else
            is_convertible<Adapted&, Base>
#endif
        >::type = 0) const
    {
        return ad;
    }

    template< class Adapted >
    Base operator()(Adapted const& ad,
        typename enable_if< is_convertible<Adapted const&, Base> >::type = 0) const
    {
        return ad;
    }

    template< class Adapted >
    Base operator()(Adapted const& ad,
        typename disable_if<is_convertible<Adapted const&, Base> >::type = 0) const
    {
        return (*this)(ad.base());
    }
};

PSTADE_SPECIFIED1(adapted_to, op_adapted_to, 1)
PSTADE_AUXILIARY(0, to_base, (automatic< op_adapted_to<_> >))


// range version
//

template< class Base >
struct op_adapted_range_to :
    callable< op_adapted_range_to<Base> >
{
    template< class Myself, class Adapted >
    struct apply
    {
        typedef Base type;
    };

    template< class Result, class Adapted >
    Result call(Adapted& ad) const
    {
        typedef typename range_iterator<Result>::type iter_t;
        return Result(
            op_adapted_to<iter_t>()(boost::begin(ad)),
            op_adapted_to<iter_t>()(boost::end(ad))
        );
    }
};

PSTADE_SPECIFIED1(adapted_range_to, op_adapted_range_to, 1)
PSTADE_AUXILIARY(0, to_base_range, (automatic< op_adapted_range_to<_> >))


} } // namespace pstade::oven


#endif
