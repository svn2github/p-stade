#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_OVEN_DEBUG
#include <pstade/oven/tests.hpp>
#include <pstade/oven/tab_expanded.hpp>
#include <pstade/oven/tab_unexpanded.hpp>


#include <fstream>
#include <iterator>
#include <string>
#include <boost/range.hpp>
#include "./core.hpp"
#include <pstade/oven/file_range.hpp>


void test()
{
    // Under vc7.1, using-directive must be here...why?
    namespace oven = pstade::oven;
    using namespace oven;

    std::string ans("TTTactor<Scpp_token::pp_include_path,TTTact_pp_include_pathS>");
    std::string src("SSSSSSSSSSSSactor<Scpp_token::pp_include_path,SSSSSSSSSSact_pp_include_pathS>");

    BOOST_CHECK( oven::equals(src|tab_unexpanded(4), ans) );

/*
    oven::file_range<> qfile("tab_expanded.txt");
    PSTADE_ASSERT( qfile.is_open() );

    oven::file_range<> afile("tab_unexpanded.txt");
    PSTADE_ASSERT( afile.is_open() );

    BOOST_CHECK( oven::equal(qfile|oven::tab_unexpanded(4), boost::begin(afile)) );
*/
/*
    oven::file_range<> sfile("tab_sample.txt");
    std::ofstream fout("tab_sample_result.txt", std::ios::binary);
    oven::copy(sfile|oven::tab_unexpanded(4), oven::outputter(fout));

 too slow
    BOOST_CHECK( oven::equal(
        qfile |
            oven::tab_unexpanded(4) |
            oven::tab_expanded(4) |
            oven::tab_unexpanded(4) |
            oven::tab_expanded(4),
        boost::begin(qfile))
    );
*/
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
