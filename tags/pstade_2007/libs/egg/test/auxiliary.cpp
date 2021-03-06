#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/auxiliary.hpp>
#include <pstade/minimal_test.hpp>


#include <string>
#include <pstade/constant.hpp>
#include <pstade/test.hpp>


#include <boost/preprocessor/facilities/identity.hpp>
#include <pstade/unparenthesize.hpp>


    #define PSTADE_AUXILIARY(N, Object, Function) \
        namespace BOOST_PP_CAT(pstade_auxiliary_workarea_of_, Object) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::result_of< ::pstade::egg::BOOST_PP_CAT(T_auxiliary, N)(PSTADE_UNPARENTHESIZE(Function)) >::type op; \
        } \
        typedef BOOST_PP_CAT(pstade_auxiliary_workarea_of_, Object)::op BOOST_PP_CAT(T_, Object); \
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_, Object)), Object) = PSTADE_EGG_AUXILIARY_L {} PSTADE_EGG_AUXILIARY_R; \
    /**/


struct impl_interface0
{
    typedef std::string result_type;

    std::string operator()(std::string const& s) const
    {
        return s + "0";
    }
};

PSTADE_AUXILIARY(0, interface0, (impl_interface0))


struct impl_interface1
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1) const
    {
        return s + ch1;
    }
};

PSTADE_CONSTANT(interface1, (pstade::result_of<pstade::egg::T_auxiliary1(impl_interface1)>::type))


struct impl_interface4
{
    typedef std::string result_type;

    std::string operator()(std::string const& s, char ch1, char ch2, char ch3, char ch4) const
    {
        return s + ch1 + ch2 + ch3 + ch4;
    }
};

PSTADE_CONSTANT(interface4, (pstade::result_of<pstade::egg::T_auxiliary4(impl_interface4)>::type))


PSTADE_TEST_IS_RESULT_OF((std::string), T_interface0(std::string))


void pstade_minimal_test()
{
    std::string s("interface");
    {
        std::string ans("interface0");
        BOOST_CHECK( interface0(s)    == ans );
        BOOST_CHECK( (s|interface0)   == ans );
        BOOST_CHECK( (s|interface0()) == ans );


        BOOST_CHECK( (interface0 |= s)    == ans );
        BOOST_CHECK( (interface0() |= s) == ans );
    }
    {
        std::string ans("interface1");
        BOOST_CHECK( interface1(s, '1')  == ans );
        BOOST_CHECK( (s|interface1('1')) == ans );

        BOOST_CHECK( (interface1('1') |= s) == ans );
    }
    {
        std::string ans("interface1234");
        BOOST_CHECK( interface4(s, '1', '2', '3', '4')  == ans );
        BOOST_CHECK( (s|interface4('1', '2', '3', '4')) == ans );

        BOOST_CHECK( (interface4('1', '2', '3', '4') |= s) == ans );
    }
}
