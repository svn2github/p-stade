#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

#include <pstade/construct.hpp>


#include <pstade/value.hpp>
#include <string>
#include <boost/utility/result_of.hpp>
#include <utility>


using namespace pstade;


std::pair<int, char> foo()
{
    return constructor(3, 'c');
}


struct eater
{
    template<class T>
    explicit eater(T) { }

    eater(int i) { }

    eater() { }
};


void eat1(eater e = constructor)
{
    (void)e;
}

void eat2()
{
    eater e = constructor;
    eater e_ = constructor();
}

void eat3(eater e  = constructor())
{
    (void)e;
}


#if !defined(__GNUC__)
// GCC prefers direct-initialization to copy-initialization
// in the case of default-argument. This must be bug of GCC.
// I don't know the exact condition; eater compiles. Why?
void buz(std::string s = constructor)
{
    (void)s;
}
#endif


void bar(std::pair<int, char> p = constructor(3, 'c'))
{
    BOOST_CHECK(p == std::make_pair(3, 'c'));
}


void test()
{
    {
        boost::result_of<op_construct<std::string>(char const*)>::type
            x = op_construct<std::string>()("hello"|to_value);
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor("hello");
        BOOST_CHECK( x == std::string("hello") );
    }
    {
        std::string x = constructor;
    }
    {
        std::string x = constructor();
    }
    {
        BOOST_CHECK(foo() == std::make_pair(3, 'c'));
    }
    {
        bar();
    }
    {
        eat1();
    }
    {
        eat2();
    }
    {
        eat3();
    }
#if !defined(__GNUC__)
    {
        buz();
    }
#endif
    {
        std::string s = constructor;
        std::string s_ = constructor;
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
