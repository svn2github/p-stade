#ifndef PSTADE_BISCUIT_PARSER_LOCALE_PREDICATE_ACTION_IS_BLANK_HPP
#define PSTADE_BISCUIT_PARSER_LOCALE_PREDICATE_ACTION_IS_BLANK_HPP


// PStade.Biscuit
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_CFG_NO_STD_LOCALE)


#include <locale>
#include <boost/foreach.hpp>
#include <boost/range/value_type.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace biscuit {


struct is_blank
{
	template< class ParsingSubRange, class UserState >
	bool operator()(ParsingSubRange& rng, UserState& us) const
	{
		std::locale loc;
		typedef typename boost::range_value<ParsingSubRange>::type value_t;
		BOOST_FOREACH (value_t const& v, rng) {
			if (!(std::isspace(v, loc) || v == '\t'))
				return false;
		}

		pstade::unused(us);
		return true;
	}
};


} } // namespace pstade::biscuit


#endif // !defined(PSTADE_CFG_NO_STD_LOCALE)


#endif
