#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.P_Stade;
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <vector>
#include <boost/foreach.hpp>


struct xxx : std::vector<int>
{
	virtual void foo() = 0;
};


void test(xxx& rng)
{
	BOOST_FOREACH (int x, rng) {
	}
}


int test_main(int, char*[])
{
    //::test();
    return 0;
}
