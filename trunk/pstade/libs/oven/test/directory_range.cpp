#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/directory_range.hpp>


#include <iostream>
#include <boost/foreach.hpp>


void test()
{
    using namespace boost;
    namespace fs = filesystem;
    using namespace pstade;
    using namespace oven;

    {
        BOOST_FOREACH (const fs::path& pt, oven::directory_range(fs::current_path())) {
            std::cout << pt.leaf() << std::endl;
        }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
