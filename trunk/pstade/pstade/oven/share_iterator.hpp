#ifndef PSTADE_OVEN_SHARE_ITERATOR_HPP
#define PSTADE_OVEN_SHARE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/shared_container_iterator.hpp>
//
// (C) Copyright Ronald Garcia 2002. Permission to copy, use, modify, sell and
// distribute this software is granted provided this copyright notice appears
// in all copies. This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.


#include <boost/iterator_adaptors.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/utility/addressof.hpp>
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


template< class Range >
struct share_iterator;


namespace share_iterator_detail {


    template< class Range >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                share_iterator<Range>,
                typename range_iterator<Range>::type
            >
        type;
    };


} // namespace share_iterator_detail


template< class Range >
struct share_iterator :
    share_iterator_detail::super_<Range>::type
{
private:
    typedef typename share_iterator_detail::super_<Range>::type super_t;
    typedef typename super_t::base_type iter_t;

public:
    share_iterator()
    { }

    share_iterator(iter_t const& it, boost::shared_ptr<Range> const& prng) :
        super_t(it), m_prng(prng)
    { }

template< class > friend struct share_iterator;
    template< class R >
    share_iterator(share_iterator<R> const& other,
        typename boost::enable_if_convertible<typename range_iterator<R>::type, iter_t>::type * = 0,
        // Prefer pointer type; 'shared_ptr' convertibility seems over-optimistic.
        typename boost::enable_if_convertible<R *, Range *>::type * = 0
    ) :
        super_t(other.base()), m_prng(other.m_prng)
    { }

    Range& base_range() const
    {
        return *m_prng;
    }

private:
    boost::shared_ptr<Range> m_prng;
};


template< class Range > inline
share_iterator<Range> const
make_share_iterator(
    typename range_iterator<Range>::type const& it,
    boost::shared_ptr<Range> const& prng)
{
    return share_iterator<Range>(it, prng);
}


} } // namespace pstade::oven


#endif
