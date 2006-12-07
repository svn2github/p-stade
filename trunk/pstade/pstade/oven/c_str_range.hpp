#ifndef PSTADE_OVEN_C_STR_RANGE_HPP
#define PSTADE_OVEN_C_STR_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <cstring> // strlen
#include <cwchar>  // wcslen
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace c_str_range_detail {


    inline
    std::size_t length(char const *psz)
    {
        using namespace std;
        return strlen(psz);
    }


    inline
    std::size_t length(wchar_t const *psz)
    {
        using namespace std;
        return wcslen(psz);
    }


} // namespace c_str_range_detail


template< class Char >
struct c_str_range :
    iter_range<Char *>::type,
    private as_lightweight_proxy< c_str_range<Char> >
{
private:
    typedef typename iter_range<Char *>::type super_t;

public:
    explicit c_str_range(Char *psz) :
        super_t(psz, psz + c_str_range_detail::length(psz))
    { }
};


namespace c_str_range_detail {


    struct baby_make
    {
        template< class Myself, class CString >
        struct apply
        {
            typedef typename pass_by_value<CString>::type ptr_t;
            typedef typename boost::remove_pointer<ptr_t>::type char_t;
            typedef c_str_range<char_t> const type;
        };

        template< class Result, class Char >
        Result call(Char *psz) const
        {
            return Result(psz);
        }
    };


} // namespace c_str_range_detail


PSTADE_EGG_FUNCTION(make_c_str_range, c_str_range_detail::baby_make)
PSTADE_PIPABLE(as_c_str, op_make_c_str_range)


} } // namespace pstade::oven


#endif
