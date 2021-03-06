#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// pythagorean triads


#include <pstade/detail/before_mpl_has_xxx.hpp>


#include <pstade/unit_test.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/comprehension.hpp>
#include <pstade/oven/counting.hpp>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/io.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>
#include <sstream>
#include <iostream>


namespace bll = boost::lambda;
using namespace pstade::oven;


typedef
    boost::tuple<int, int, int>
triple_t;

struct make_triple
{
    typedef triple_t result_type;

    result_type operator()(int x, int y, int z) const
    {
        return result_type(x, y, z);
    }
};


typedef
    any_range<triple_t, boost::forward_traversal_tag>
triples_t;

triples_t triples(int n)
{
    return
        comprehension(
            ::make_triple(),
            always_return(true),
            always_return(counting(1, n+1)),
            bll::bind(counting, bll::_1, n+1),
            bll::bind(counting, bll::_2, n+1)
        );
}


bool pyth(boost::tuple<int, int, int> t)
{
    int x, y, z;
    boost::tie(x, y, z) = t;
    return x*x + y*y == z*z;
}


triples_t triads(int n)
{
    return
        triples(n)|filtered(&::pyth);
}


void pstade_unit_test()
{
    std::stringstream sout;
    sout << ::triads(20);
    BOOST_CHECK(sout.str() == "{(3 4 5),(5 12 13),(6 8 10),(8 15 17),(9 12 15),(12 16 20)}");
}
