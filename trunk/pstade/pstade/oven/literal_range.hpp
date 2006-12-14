#ifndef PSTADE_OVEN_LITERAL_RANGE_HPP
#define PSTADE_OVEN_LITERAL_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2006/n2059.html#as-literal
// Oven's 'as_literal' supports only const array types.
// Consider "hello\0secret".
// What should 'boost::to_upper("hello\0secret")' do?
// So Oven has another function 'as_c_str'.
// "hello\0secret"|as_literal      == *hello\0secret*
// "hello\0secret"|as_c_str        == *hello*
// "hello\0secret"|array_protected == *hello\0secret\0*


#include <cstddef> // size_t
#include <boost/type_traits/remove_const.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


template< class Char >
struct literal_range :
    iter_range<Char const *>::type,
    private as_lightweight_proxy< literal_range<Char> >
{
    typedef literal_range type;

private:
    typedef typename iter_range<Char const *>::type super_t;

public:
    template< std::size_t sz >
    explicit literal_range(Char const (&arr)[sz]) :
        super_t(
            static_cast<Char const *>(arr),
            static_cast<Char const *>(arr) + sz - 1
        )
    { }
};


template< class Array >
struct deduce_to_array_element_non_const :
    deduce_to< Array, boost::remove_const<typename boost::remove_extent<Array>::type> >
{ };


PSTADE_OBJECT_GENERATOR(make_literal_range,
    (literal_range< deduce_to_array_element_non_const<from_1> >) const)
PSTADE_PIPABLE(as_literal, (op_make_literal_range))


} } // namespace pstade::oven


#endif
