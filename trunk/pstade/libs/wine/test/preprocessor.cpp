#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/preprocessor.hpp>


#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <pstade/unused.hpp>


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void foo( PSTADE_PP_ENUM_REF_PARAMS(5, A, a) )
{
    pstade::unused(a0, a1, a2, a3, a4);
    return;
}

template< BOOST_PP_ENUM_PARAMS(5, class A) >
void foo_( PSTADE_PP_ENUM_REFS(5, A) )
{
    return;
}


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void cfoo( PSTADE_PP_ENUM_CREF_PARAMS(5, A, a) )
{
    pstade::unused(a0, a1, a2, a3, a4);
    return;
}


template< BOOST_PP_ENUM_PARAMS(5, class A) >
void cfoo_( PSTADE_PP_ENUM_CREFS(5, A) )
{
    return;
}


PSTADE_PP_DECLARE_TYPE(struct, (aaa))
PSTADE_PP_DECLARE_TYPE(struct, (naaa)(nbbb)(ccc))

PSTADE_PP_DECLARE_TEMPLATE(struct, (taaa), (class)(int)(char))
PSTADE_PP_DECLARE_TEMPLATE(struct, (naaa)(nbbb)(tccc1), 3)
PSTADE_PP_DECLARE_TEMPLATE(struct, (naaa)(nbbb)(tccc2), (class)(int)(unsigned int))


template< class A >
void rfoo( BOOST_PP_SEQ_ENUM( PSTADE_PP_SEQ_REPLICATE(5, A) ) )
{ }


template< class A >
void cyfoo( BOOST_PP_SEQ_ENUM( PSTADE_PP_SEQ_CYCLE(3, (A)(A)) ) )
{ }


template< class A >
void to_seq( BOOST_PP_SEQ_ENUM( PSTADE_PP_SEQ_TO_SEQ(~, (A)) ) )
{ }

template< class A >
void to_seq2( BOOST_PP_SEQ_ENUM( PSTADE_PP_SEQ_TO_SEQ((A)(A), (A)) ) )
{ }


void test()
{
    int i = 0;
    ::foo(i, i, i, i, i);
    ::foo_(i, i, i, i, i);

    ::cfoo(1, 1, 1, 1, 1);
    ::cfoo_(1, 1, 1, 1, 1);

    ::rfoo(1, 1, 1, 1, 1);
    ::cyfoo(1, 1, 1, 1, 1, 1);

    ::to_seq(1);
    ::to_seq2(1, 1);
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
