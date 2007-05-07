#ifndef PSTADE_OVEN_DEREF_HPP
#define PSTADE_OVEN_DEREF_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A dereference of ReadableIterator returns a type "convertible" to
// associated 'value_type', but it is useless for writing generic code.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace deref_detail {


    template< class Value, class Reference >
    struct result_
    {
        typedef
            boost::mpl::or_<
                boost::is_same<Value&, Reference>,
                boost::is_same<Value const&, Reference>,
                boost::is_same<Value const volatile&, Reference>
            >
        is_ref;

        typedef typename
            boost::mpl::if_< is_ref,
                Reference,
                Value
            >::type
        type;
    };


    template< class ReadableOrLvalueIter >
    struct baby
    {
        typedef typename
            boost::remove_const<ReadableOrLvalueIter>::type
        iter_t;

        typedef typename
            result_<
                typename boost::iterator_value<iter_t>::type,
                typename boost::iterator_reference<iter_t>::type
            >::type
        result_type;

        // Pass by reference; see "./reverse_iterator.hpp"
        result_type operator()(ReadableOrLvalueIter& it) const
        {
            return *it;
        }
    };


} // namespace deref_detail


PSTADE_FUNCTION(deref, (deref_detail::baby<_>))


} } // namespace pstade::oven


#endif
