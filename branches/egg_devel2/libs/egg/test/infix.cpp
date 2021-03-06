

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/infix.hpp>
#include "./egg_test.hpp"


#include <boost/egg/to_string.hpp>
#include <boost/egg/functional.hpp> // plus
#include <string>


struct str_plus_int
{
    typedef std::string result_type;

    result_type operator()(std::string s, int i) const
    {
        return s + boost::egg::to_string(i);
    }
};


void egg_test()
{
    using boost::egg::plus;

    {
        using namespace boost::egg::infix;

        std::string l("hello");
        int r = 12;
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ 12) == "hello12" );
        BOOST_CHECK( (std::string("hello") ^str_plus_int()^ r) == "hello12" );
        BOOST_CHECK( (l ^str_plus_int()^ r) == "hello12" );
    }
    {
        using namespace boost::egg::infix;

        int l = 10, r = 12;
        BOOST_CHECK( (10 ^plus^ 12) == 22 );
        BOOST_CHECK( (l ^plus^ 12) == 22 );
        BOOST_CHECK( (10 ^plus^ r) == 22 );
        BOOST_CHECK( (l ^plus^ r) == 22 );
    }
    {
        using namespace boost::egg::infix;

        BOOST_CHECK( (10 ^plus^ 12 ^plus^ 3) == 25 );
    }
}
