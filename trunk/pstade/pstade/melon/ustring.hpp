#ifndef PSTADE_MELON_USTRING_HPP
#define PSTADE_MELON_USTRING_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string> // basic_string
#include <vector>
#include <boost/mpl/bool.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/basic_ostream_fwd.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include "./ucs4_t.hpp"


namespace pstade { namespace melon {


namespace ustring_detail {


    template< class = void >
    struct super_
    {
        typedef std::vector<melon::ucs4_t> type;
    };


} // namespace ustring_detail


struct ustring :
    ustring_detail::super_<>::type
{
private:
    typedef ustring_detail::super_<>::type super_t;

public:
    explicit ustring()
    { }

    explicit ustring(super_t::size_type n) :
        super_t(n)
    { }

    explicit ustring(super_t::size_type n, const super_t::value_type& t) :
        super_t(n, t)
    { }

    template< class Iterator >
    explicit ustring(Iterator f, Iterator l) :
        super_t(f, l)
    { }

    template< class Range >
    explicit ustring(const Range& rng) :
        super_t(boost::begin(rng), boost::end(rng))
    { }

    // Constructor prefers copy constructor and converts argument to ustring.
    // But operator= doesn't, so be strict.
    template< class Range > 
    typename boost::enable_if<apple::is_boost_range<Range>, ustring&>::type
    operator=(const Range& rng)
    {
        assign(boost::begin(rng), boost::end(rng));
        return *this;
    }

    // implicit conversions
    //
    ustring(char *psz) :
        super_t(psz, oven::null_terminate_range_detail::end(psz))
    { }

    ustring(wchar_t *psz) :
        super_t(psz, oven::null_terminate_range_detail::end(psz))
    { }
};


// truncated!
//

template<class CharT, class Traits >
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, ustring str)
{
    os << oven::sequence_cast< std::basic_string<CharT, Traits> >(str);
    return os;
}


template<class CharT, class Traits >
std::basic_istream<CharT, Traits>& operator>>(std::basic_istream<CharT, Traits>& os, ustring& str)
{
    std::basic_string<CharT, Traits> tmp;
    os >> tmp;
    str = melon::ustring(tmp);
    return os;
}


} } // namespace pstade::melon


namespace pstade { namespace apple {


template< >
struct is_sequence_impl<melon::ustring> :
    boost::mpl::true_
{ };


} } // namespace pstade::apple


#endif
