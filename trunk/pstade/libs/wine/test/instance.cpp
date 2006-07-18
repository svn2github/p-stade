#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


#include <string>
#include <map>
#include <boost/noncopyable.hpp>
#include <pstade/comma_protect.hpp>


struct aaa
{
    aaa(char, int, double)
    { }
};


struct bbb : private boost::noncopyable
{
    bbb(std::string str) :
        m_str(str)
    { }

    std::string m_str;
};


PSTADE_INSTANCE(int, x, value)
PSTADE_INSTANCE(const int, cx, value)
PSTADE_INSTANCE(aaa, a, ('a')(10)(3.5))
PSTADE_INSTANCE(bbb, b, ("hello"))


PSTADE_INSTANCE(int, x1, (12))
PSTADE_INSTANCE(int const, cx1, (12))


PSTADE_INSTANCE(const char *, sz, ("hello"))
PSTADE_INSTANCE(std::string, str, (sz))
PSTADE_INSTANCE(const std::string, cstr, (str))
PSTADE_INSTANCE(std::string const, cstr2, value)
PSTADE_INSTANCE(PSTADE_COMMA_PROTECT((std::map<int, int>)), map1_, value)
PSTADE_INSTANCE(PSTADE_COMMA_PROTECT((std::map<int, int>)) const, map2_, value)


template< class T >
void const_check(T const&)
{ }

template< class T >
void const_check(T&)
{
    BOOST_CHECK(false);
}


void test()
{
    BOOST_CHECK(x == 0);
    BOOST_CHECK(cx == 0);
    x = x1;
    BOOST_CHECK(x == x1);
    BOOST_CHECK(x1 == cx1);
    BOOST_CHECK(b.m_str == "hello");
    BOOST_CHECK(x1 == 12);
    BOOST_CHECK(str == sz);
    BOOST_CHECK(cstr == sz);
    map1_[12] = 13;

    ::const_check(cx);
    ::const_check(cx1);
    ::const_check(cstr);
    ::const_check(cstr2);
    ::const_check(map2_);

    BOOST_CHECK(pstade_instance_of_str() == sz);
    BOOST_CHECK(pstade_instance_of_cstr() == sz);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
