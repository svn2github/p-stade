#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/compile.hpp>


#include <string>
#include <list>
#include <vector>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/taken.hpp>
#include <pstade/oven/identities.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string       rng1("12");
        std::list<char>   rng2 = std::string("34")|copied;
        std::vector<char> rng3 = std::string("56")|copied;

        BOOST_CHECK( equals(
            compile( +(rng1 >> (rng2|as_term) >> rng3) ) | taken(17),
            std::string("12345612345612345")
        ) );
    }
}


#if 0
void test_()
{
    {
        std::string       rng1("12");
        std::list<char>   rng2 = std::string("34")|copied;
        std::vector<char> rng3 = std::string("56")|copied;
        std::string       rng4_("78");
        test_noncopyable_range<std::string> rng4(rng4_);

        BOOST_CHECK( equals(
            compile( +(rng1 >> (rng2|as_expr) >> rng3) ) | taken(18),
            std::string("123456123456123456")
        ) );
    }
}
#endif


int test_main(int, char*[])
{
    ::test();
    return 0;
}
