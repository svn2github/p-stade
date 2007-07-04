#include <pstade/vodka/drink.hpp>


// PStade.Fat
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/fat/new.hpp>
#include <pstade/unit_test.hpp>


#include <pstade/test.hpp>


namespace fat = pstade::fat;
using namespace fat;


struct udt
{
    udt(int i, int j)
        : m_i(i), m_j(j)
    { }

    int m_i, m_j;
};


PSTADE_TEST_IS_RESULT_OF((int *), xp_new_<int>())
PSTADE_TEST_IS_RESULT_OF((int *), xp_new_<int>(int))


PSTADE_TEST_IS_RESULT_OF((udt *), xp_new_<udt>(int,int))
PSTADE_TEST_IS_RESULT_OF((udt const*), xp_new_<udt const>(int,int))


void pstade_unit_test()
{
    {
        udt *p = xp_new_<udt>()(1,2);
        BOOST_CHECK(p->m_i == 1);
        BOOST_CHECK(p->m_j == 2);
        delete p;
    }
}
