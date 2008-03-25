

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/uncurry.hpp>
#include <boost/egg/curry.hpp>
#include "./egg_test.hpp"


#include <boost/egg/to_string.hpp>
#include <boost/egg/const.hpp>

using boost::egg::to_string;


struct my_plus2
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2>
    struct result<Self(Int1, Int2)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y) const
    {
        return to_string(x) + to_string(y);
    }
};

typedef boost::egg::result_of_curry2<my_plus2>::type T_curried_plus2;
BOOST_EGG_CONST((T_curried_plus2), curried_plus2) = BOOST_EGG_CURRY2({});

typedef boost::egg::result_of_uncurry<T_curried_plus2>::type T_still_plus2;
BOOST_EGG_CONST((T_still_plus2), still_plus2) = BOOST_EGG_UNCURRY_L BOOST_EGG_CURRY2_L {} BOOST_EGG_CURRY2_R BOOST_EGG_UNCURRY_R;


struct my_plus3
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3>
    struct result<Self(Int1, Int2, Int3)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z) const
    {
        return to_string(x) + to_string(y) + to_string(z);
    }
};


struct my_plus4
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4>
    struct result<Self(Int1, Int2, Int3, Int4)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z, int q) const
    {
        return to_string(x) + to_string(y) + to_string(z) + to_string(q);
    }
};


struct my_plus5
{
    template<class Signature>
    struct result;

    template<class Self, class Int1, class Int2, class Int3, class Int4, class Int5>
    struct result<Self(Int1, Int2, Int3, Int4, Int5)>
    {
        typedef std::string type;
    };

    std::string operator()(int x, int y, int z, int q, int r) const
    {
        return to_string(x) + to_string(y) + to_string(z) + to_string(q) + to_string(r);
    }
};

typedef boost::egg::result_of_curry5<my_plus5>::type T_curried_plus5;
BOOST_EGG_CONST((T_curried_plus5), curried_plus5) = BOOST_EGG_CURRY5_L {} BOOST_EGG_CURRY5_R;

typedef boost::egg::result_of_uncurry<T_curried_plus5>::type T_still_plus5;
BOOST_EGG_CONST((T_still_plus5), still_plus5) = BOOST_EGG_UNCURRY_L BOOST_EGG_CURRY5_L {} BOOST_EGG_CURRY5_R BOOST_EGG_UNCURRY_R;


void egg_test()
{
    using namespace boost::egg;

    {
        BOOST_CHECK(
            uncurry(curry2(::my_plus2()))(5, 7) == "57"
        );
    }
    {
        BOOST_CHECK(
            still_plus2(5, 7) == "57"
        );
    }
    {
        BOOST_CHECK(
            uncurry(curry3(::my_plus3()))(5, 7, 2) == "572"
        );
    }
    {
        BOOST_CHECK(
            uncurry(curry4(::my_plus4()))(5, 7, 2, 3) == "5723"
        );
    }
    {
        BOOST_CHECK(
            uncurry(curry5(::my_plus5()))(5, 7, 2, 3, 4) == "57234"
        );
    }
    {
        BOOST_CHECK(
            still_plus5(5, 7, 2, 3, 4) == "57234"
        );
    }
}
