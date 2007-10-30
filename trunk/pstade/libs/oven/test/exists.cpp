#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/exists.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/result_of.hpp>
#include <pstade/test.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_TEST_IS_RESULT_OF((bool), T_exists(std::string&))


struct is_a
{
    bool operator()(char ch) const
    {
        return ch == 'a';
    }
};


void pstade_minimal_test()
{
    {
        BOOST_CHECK( exists(std::string("bbbbbbbabb"), is_a()) );
        BOOST_CHECK(!exists(std::string("bbbbbbbbbb"), is_a()) );
    }
}
