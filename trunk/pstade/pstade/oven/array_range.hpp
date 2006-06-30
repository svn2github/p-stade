#ifndef PSTADE_OVEN_ARRAY_RANGE_HPP
#define PSTADE_OVEN_ARRAY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/noncopyable.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/scoped_array.hpp>
#include <boost/utility/base_from_member.hpp>


namespace pstade { namespace oven {


template< class Value >
struct array_range :
    private boost::base_from_member< boost::scoped_array<Value> >,
    boost::iterator_range<Value *>,
    private boost::noncopyable
{
private:
    typedef boost::base_from_member< boost::scoped_array<Value> > scoped_array_bt;
    typedef boost::iterator_range<Value *> super_t;

public:
    explicit array_range(std::size_t sz) :
        scoped_array_bt(new Value[sz]),
        super_t(scoped_array_bt::member.get(), scoped_array_bt::member.get() + sz)
    { }
};


} } // namespace pstade::oven


#endif
