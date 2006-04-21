#ifndef PSTADE_MELON_STAG_HPP
#define PSTADE_MELON_STAG_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./Attribute.hpp"
#include "./S.hpp"
#include "./Name.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class Name_ = default_,
    class Attribute_ = default_,
    class S_ = default_
>
struct STag :
    biscuit::seq<
        biscuit::chseq<'<'>,
        typename detail::if_default<Name<>, Name_>::type,
        biscuit::star<
            biscuit::seq<
                typename detail::if_default<S<>, S_>::type,
                typename detail::if_default<Attribute<>, Attribute_>::type
            >
        >,
        biscuit::opt<typename detail::if_default<S<>, S_>::type>,
        biscuit::chseq<'>'>
    >
{ };


} } // namespace pstade::melon


#endif
