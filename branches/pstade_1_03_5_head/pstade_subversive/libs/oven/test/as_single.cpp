#include <pstade/unit_test.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/as_single.hpp>


#include <memory>
#include <string>
#include <vector>
#include "./core.hpp"
#include <pstade/new_delete.hpp>


void pstade_unit_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("a");

    {
        BOOST_CHECK( oven::equals('a'|as_single, ans) );
    }
    {
        BOOST_CHECK( oven::equals(as_single('a'), ans) );
    }
    {
        char ch = 'a';
        BOOST_CHECK( oven::equals(oven::as_single(ch), ans) );
    }

    {
        BOOST_CHECK( oven::equals(new char('a')|as_shared_single, ans) );
    }

    {
        BOOST_CHECK( oven::equals(as_shared_single(pstade::op_new_auto<char>()('a')), ans) );
        BOOST_CHECK( oven::equals(pstade::op_new_auto<char>()('a')|as_shared_single, ans) );
    }
}

