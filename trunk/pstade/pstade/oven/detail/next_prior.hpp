#ifndef PSTADE_OVEN_DETAIL_NEXT_PRIOR_HPP
#define PSTADE_OVEN_DETAIL_NEXT_PRIOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// replaces <boost/next_prior.hpp>.
// "../distance.hpp" tells why.


#include <iterator> // advance
#include <boost/iterator/iterator_categories.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator, class Difference > inline
void traversal_advance(Iterator& it, Difference d, boost::random_access_traversal_tag)
{
    it += d;
}

template< class Iterator, class Difference > inline
void traversal_advance(Iterator& it, Difference d, boost::single_pass_traversal_tag)
{
    std::advance(it, d);
}


template< class Iterator > inline
Iterator next(Iterator it)
{
    return ++it;
}

template< class Iterator, class Difference > inline
Iterator next(Iterator it, Difference d)
{
    typedef typename boost::iterator_traversal<Iterator>::type trv_t;
    detail::traversal_advance(it, d, trv_t());
    return it;
}


template< class Iterator > inline
Iterator prior(Iterator it)
{
  return --it;
}

template< class Iterator, class Difference > inline
Iterator prior(Iterator it, Difference d)
{
    typedef typename boost::iterator_traversal<Iterator>::type trv_t;
    detail::traversal_advance(it, -d, trv_t());
    return it;
}


} } } // namespace pstade::oven::detail


#endif