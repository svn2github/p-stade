#pragma once

#include <boost/config.hpp>
#include "./chsetn.hpp"


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
		#include "../../detail/preprocessing/chset.hpp"
	#else
		#include "../../detail/preprocessed/chset.hpp"
	#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
