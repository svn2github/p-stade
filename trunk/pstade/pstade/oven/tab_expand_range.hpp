#ifndef PSTADE_OVEN_TAB_EXPAND_RANGE_HPP
#define PSTADE_OVEN_TAB_EXPAND_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/utility/base_from_member.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/config.hpp" // DEBUG_SPACE_CH
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


namespace tab_expand_range_detail {


	template< class ForwardRange >
	struct super_
	{
		typedef boost::iterator_range<
			tab_expand_iterator<
				typename boost::range_result_iterator<ForwardRange>::type
			>
		> type;
	};


} // namespace tab_expand_range_detail


template< class ForwardRange >
struct tab_expand_range :
	private boost::base_from_member<typename boost::range_value<ForwardRange>::type>,
	tab_expand_range_detail::super_<ForwardRange>::type
{
private:
	typedef boost::base_from_member<typename boost::range_value<ForwardRange>::type> initializer_t;
	typedef typename tab_expand_range_detail::super_<ForwardRange>::type super_t;
	typedef typename super_t::iterator iter_t;

public:
	explicit tab_expand_range(ForwardRange& rng, int tabsize) :
		initializer_t(PSTADE_OVEN_DEBUG_SPACE_CH),
		super_t(
			iter_t(boost::begin(rng), tabsize, initializer_t::member),
			iter_t(boost::end(rng), tabsize, initializer_t::member)
		)
	{ }
};


namespace tab_expand_range_detail {


	struct baby_generator
	{
		template< class ForwardRange, class TabSizeT >
		struct apply
		{
			typedef const tab_expand_range<ForwardRange> type;
		};

		template< class Result, class ForwardRange >
		Result call(ForwardRange& rng, int tabsize)
		{
			return Result(rng, tabsize);
		}
	};


} // namespace tab_expand_range_detail


PSTADE_EGG_FUNCTION(make_tab_expand_range, tab_expand_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(tab_expanded, tab_expand_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::tab_expand_range, 1)


#endif
