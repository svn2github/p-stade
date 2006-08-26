#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_WINE_TEST_MINIMAL
#endif

#if !defined(PSTADE_WINE_TEST_MINIMAL)
    #include <boost/test/test_tools.hpp>
    #define BOOST_LIB_NAME boost_test_exec_monitor
    #include <boost/config/auto_link.hpp>
#else
    #include <boost/test/minimal.hpp>
#endif


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/contract.hpp>


#include <cmath>
#include <iostream>
#include <sstream>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_integral.hpp>


using namespace pstade;


template< class T >
void bar(T i)

{
    PSTADE_PRECONDITION
    {
        assert(PSTADE_IMPLIES(i == 100, i < 200));
    }

    ++i;

    PSTADE_POSTCONDITION
    {
        assert(PSTADE_IMPLIES(i != 100, i != 100));
    }
}


inline
float square_root(float x)
{
    PSTADE_PRECONDITION
    {
        assert(x >= 0);
    }

    float result = std::sqrt(x);

    PSTADE_POSTCONDITION
    {
        assert((result * result) == x);
    }
    return result;
}


struct date
{
    date(int day, int hour) :
        m_day(day), m_hour(hour)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION
        { }
    }

    void set_day(int day)
    {
        PSTADE_PUBLIC_PRECONDITION
        {
            assert(1 <= day && day <= 31);
        }

        m_day = day;
    }

private:
    PSTADE_CLASS_INVARIANT
    {
        assert(1 <= m_day && m_day <= 31);
        assert(0 <= m_hour && m_hour < 24);
    }

    int m_day, m_hour;
};


template< class T >
struct A
{
private:
    PSTADE_CLASS_INVARIANT
    {
        BOOST_MPL_ASSERT((boost::is_integral<T>)); // bad style?
    }
};


struct B : A<int>
{
    B(int f, int l) :
        m_f(f)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION
        {
            assert(f <= l);
        }

        // set up here
        m_l = l;
    }

    ~B()
    {
        PSTADE_DESTRUCTOR_PRECONDITION
        { }

        // clean up here

        m_f = 500; // violate it here, but ok.
    }
    
    void set_f(int f)
    {
        PSTADE_PUBLIC_PRECONDITION
        {
            if (f != 9898)
                assert(f <= m_l);
        }

        m_f = f;
    }

    void barbar()
    {
        PSTADE_PUBLIC_PRECONDITION
        { }
    }

    void foofoo(int i)

    {
        PSTADE_PRECONDITION
        {
            assert(i == 10);
        }

        m_f = i;
    }

private:
    int m_f, m_l;

    PSTADE_CLASS_INVARIANT
    {
        pstade::invariant< A<int> >(*this); // you should call

        assert(m_f != 500);
        assert(PSTADE_IMPLIES(m_f == 10492, m_l != 999));
    }
};


std::stringstream g_ss;

struct test_man
{
    test_man()
    {
        PSTADE_CONSTRUCTOR_PRECONDITION
        {
            g_ss << "_pc_";
        }

        g_ss << "_bc_";
    }

    ~test_man()
    {
        PSTADE_DESTRUCTOR_PRECONDITION
        {
            g_ss << "_pd_";
        }

        g_ss << "_bd_";
    }

    void do_it1()
    {
        PSTADE_PUBLIC_PRECONDITION
        {
            g_ss << "_p1_";
        }

        g_ss << "_b1_";
    }

    void do_it2()
    {
        PSTADE_PRECONDITION
        {
            g_ss << "_p2_";
        }

        g_ss << "_b2_";
    }

private:
    PSTADE_CLASS_INVARIANT
    {
        g_ss << "_I_";
    }
};


void test()
{
    ::bar(9);
    
    B b(80, 5000);
    b.set_f(80);
    
    for (int i = 0;;) {
        PSTADE_INVARIANT { assert(i < 10); }

        if (++i == 10)
            break;
    }

    (void)b;

    ::square_root(6400);

    ::date d(30, 13);

    PSTADE_INVARIANT
    {
        std::cout << "test_man test\n";
        ::test_man man;
        assert( g_ss.str() == "_pc__bc__I_" );
        g_ss.str("");
        man.do_it1();
        assert( g_ss.str() == "_I__p1__b1__I_" );
        g_ss.str("");
        man.do_it2();
        assert( g_ss.str() == "_p2__b2_" );
        g_ss.str("");
    }
    PSTADE_INVARIANT
    {
        assert( g_ss.str() == "_I__pd__bd_" );
    }
}


#if !defined(PSTADE_WINE_TEST_MINIMAL)

    #include <boost/test/unit_test.hpp>
    using boost::unit_test::test_suite;

    test_suite *
    init_unit_test_suite(int argc, char *argv[])
    {
        test_suite *test = BOOST_TEST_SUITE("Oven Test Suite");
        test->add(BOOST_TEST_CASE(&::test));

        (void)argc, (void)argv; // unused
        return test;
    }

#else

    int test_main(int, char*[])
    {
        ::test();
        return 0;
    }

#endif
