#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/as.hpp>


#include <vector>
#include <boost/range.hpp>
#include <pstade/test.hpp>


PSTADE_TEST_IS_RESULT_OF((int&), pstade::op_as_ref(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), pstade::op_as_ref(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), pstade::op_as_ref(int))

PSTADE_TEST_IS_RESULT_OF((int const&), pstade::op_as_cref(int&))
PSTADE_TEST_IS_RESULT_OF((int const&), pstade::op_as_cref(int const&))
PSTADE_TEST_IS_RESULT_OF((int const&), pstade::op_as_cref(int))


PSTADE_TEST_IS_RESULT_OF((int), pstade::op_as_value(int&))
PSTADE_TEST_IS_RESULT_OF((int), pstade::op_as_value(int const&))

PSTADE_TEST_IS_RESULT_OF((int *), pstade::op_as_value(int (&)[5]))
PSTADE_TEST_IS_RESULT_OF((int const *), pstade::op_as_value(int const (&)[5]))


template< class T >
void foo(T& )
{ }


void test()
{
    using namespace pstade;

    ::foo(pstade::as_ref(1));
    ::foo(1|as_ref);
}


template< class Fun, class T >
void apply(Fun f, T& x)
{
    f(x);
}


inline void reset(double& d) { d = 0.0; }
inline void resee(double ) { /*output value*/ }


void ctest()
{
    {
        typedef std::vector<int> vector_t;
        typedef vector_t::const_iterator citer_t;
        
        vector_t v;
        
        citer_t it0 = const_cast<vector_t const&>(v).begin();
        citer_t it1 = static_cast<citer_t>(v.begin());
        citer_t it2 = v.begin();
        
        citer_t it3 = boost::const_begin(v);
        citer_t it4 = pstade::as_cref(v).begin();
        citer_t it5 = boost::begin(pstade::as_cref(v));
   }

    {
        double d = 3;
        d = d*d;
        d = d/d;
        
        ::apply(::reset, d); // oops: resee intended
        BOOST_CHECK(d == 0.0);
    }

    {
        double d = 3;
        d = d*d;
        d = d/d;

        // ::apply(::reset, pstade::as_cref(d)); // error!
        ::apply(::resee, pstade::as_cref(d));
        ::apply(::resee, d|pstade::as_cref);
    }

#if 0
    {
        double d = 3;
        d = d*d;
        d = d/d;
        // ::apply(::reset, d|pstade::as_cref); // error!
        ::apply(::resee, d|pstade::as_cref);
    }
#endif

    {
        BOOST_CHECK( pstade::as_value(3) == 3 );
        BOOST_CHECK( (3|pstade::as_value) == 3 );
        BOOST_CHECK( (3|pstade::as_value()) == 3 );

        int arr[3];
        int *parr = pstade::as_value(arr);
        parr = arr|pstade::as_value;
    }
}


int test_main(int, char*[])
{
    ::test();
    ::ctest();
    return 0;
}
