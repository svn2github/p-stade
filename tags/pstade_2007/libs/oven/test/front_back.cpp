#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/front.hpp>
#include <pstade/oven/back.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>


void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("f12344513215b");
        BOOST_CHECK( front(str) == 'f' );
        BOOST_CHECK( back(str)  == 'b' );
        BOOST_CHECK( value_front(str) == 'f' );
        BOOST_CHECK( value_back(str)  == 'b' );

        front(str) = 'g';
        back(str) = 'c';
        BOOST_CHECK( str == "g12344513215c" );
    }
}

