#ifndef PSTADE_OVEN_TOKENIZED_HPP
#define PSTADE_OVEN_TOKENIZED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/regex.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/pipable.hpp>
#include <pstade/use_default.hpp>
#include "./iter_range.hpp"
#include "./concepts.hpp"
#include "./extension.hpp"
#include "./range_iterator.hpp"
#include "./range_value.hpp"


namespace pstade { namespace oven {


template<
    class CharT  = boost::use_default,
    class Traits = boost::use_default
>
struct op_make_tokenized :
    callable< op_make_tokenized<CharT, Traits> >
{
    template< class Myself, class Range, class Regex, class IntOrRandRange = void, class Flag  = void >
    struct apply
    {
        typedef typename
            use_default_eval_to< CharT, range_value<Range> >::type
        char_t;

        typedef typename
            use_default_to< Traits, boost::regex_traits<char_t> >::type
        traits_t;

        typedef
            boost::regex_token_iterator<
                typename range_iterator<Range>::type,
                char_t,
                traits_t                
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range, class Regex >
    Result call(
        Range& rng, Regex& re,
        int submatch = 0,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
    ) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, submatch, flag),
            iter_t()
        );
    }

    template< class Result, class Range, class Regex, class RandRange >
    Result call(
        Range& rng, Regex& re,
        RandRange const& submatches,
        boost::regex_constants::match_flag_type flag = boost::regex_constants::match_default
#if defined(__GNUC__) // See <pstade/const_overloaded.hpp>.
        , typename disable_if< boost::is_same<int, RandRange> >::type = 0
#endif
    ) const
    {
        PSTADE_CONCEPT_ASSERT((Bidirectional<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng), re, submatches, flag),
            iter_t()
        );
    }
};


PSTADE_CONSTANT(make_tokenized, (op_make_tokenized<>))
PSTADE_PIPABLE(tokenized, (op_make_tokenized<>))


} } // namespace pstade::oven


#endif
