#ifndef PSTADE_BISCUIT_ALGORITHM_PARSE_HPP
#define PSTADE_BISCUIT_ALGORITHM_PARSE_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/oven/iter_range.hpp>
#include <pstade/oven/sub_range_result.hpp>
#include "../match_results/default_type.hpp"
#include "../state/null_state.hpp"
#include "../state/parsing_range_state_type.hpp"


namespace pstade { namespace biscuit {


namespace parse_detail {


    template< class Parser, class ParsingRange, class MatchResults, class UserState >
    typename oven::sub_range_result<ParsingRange>::type
    aux(ParsingRange& r, MatchResults& rs, UserState& us)
    {
        typedef typename parsing_range_state<ParsingRange, MatchResults>::type state_t;

        state_t s(r, rs);
        Parser::parse(s, us);
        return oven::make_iter_range(boost::begin(s), s.get_cur());
    }


} // namespace parse_detail


template< class Parser, class ForwardRange, class UserState > inline
typename oven::sub_range_result<ForwardRange>::type
parse(ForwardRange& r, UserState& us PSTADE_CONST_OVERLOADED(ForwardRange))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return parse_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class UserState > inline
    typename oven::sub_range_result<PSTADE_DEDUCED_CONST(ForwardRange)>::type
    parse(ForwardRange const& r, UserState& us)
    {
        typedef typename match_results_default<Parser, PSTADE_DEDUCED_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return parse_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange > inline
typename oven::sub_range_result<ForwardRange>::type
parse(ForwardRange& r PSTADE_CONST_OVERLOADED(ForwardRange))
{
    typedef typename match_results_default<Parser, ForwardRange>::type results_t;
    results_t rs;
    return parse_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange > inline
    typename oven::sub_range_result<PSTADE_DEDUCED_CONST(ForwardRange)>::type
    parse(ForwardRange const& r)
    {
        typedef typename match_results_default<Parser, PSTADE_DEDUCED_CONST(ForwardRange)>::type results_t;
        results_t rs;
        return parse_detail::aux<Parser>(r, rs, null_state);
    }


template< class Parser, class ForwardRange, class MatchResults, class UserState > inline
typename oven::sub_range_result<ForwardRange>::type
results_parse(ForwardRange& r, MatchResults& rs, UserState& us PSTADE_CONST_OVERLOADED(ForwardRange))
{
    return parse_detail::aux<Parser>(r, rs, us);
}

    template< class Parser, class ForwardRange, class MatchResults, class UserState > inline 
    typename oven::sub_range_result<PSTADE_DEDUCED_CONST(ForwardRange)>::type
    results_parse(ForwardRange const& r, MatchResults& rs, UserState& us)
    {
        return parse_detail::aux<Parser>(r, rs, us);
    }


// no user-state
template< class Parser, class ForwardRange, class MatchResults > inline
typename oven::sub_range_result<ForwardRange>::type
results_parse(ForwardRange& r, MatchResults& rs PSTADE_CONST_OVERLOADED(ForwardRange))
{
    return parse_detail::aux<Parser>(r, rs, null_state);
}

    template< class Parser, class ForwardRange, class MatchResults > inline
    typename oven::sub_range_result<PSTADE_DEDUCED_CONST(ForwardRange)>::type
    results_parse(ForwardRange const& r, MatchResults& rs)
    {
        return parse_detail::aux<Parser>(r, rs, null_state);
    }


} } // namespace pstade::biscuit


#endif
