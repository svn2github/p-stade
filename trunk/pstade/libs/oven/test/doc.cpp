#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven.hpp>


#include <locale>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <pstade/egg/function.hpp>


struct baby_to_lower
{
    template< class CharT >
    struct result : boost::remove_const<CharT>
    { };

    template< class Result, class CharT >
    Result call(CharT ch)
    {
        return std::tolower(ch, std::locale());
    }
};


PSTADE_EGG_FUNCTION(to_lower, baby_to_lower)


using namespace pstade;
using namespace oven;


void test_introduction()
{
    {
        using namespace boost;

        std::vector<char> out;

        BOOST_FOREACH (char ch,
            new std::string("!ExGNxxAR ,xOLxLExH")
                | shared
                | filtered(lambda::_1 != 'x')
                | reversed
                | transformed(::to_lower)
                | memoized
        ) {
            out.push_back(ch);
        }

        BOOST_CHECK( oven::equals(out, "hello, range!"|null_terminated) );
    }
}


void test_stl_algorithms()
{
    std::string str;

    // iterator-based
    str = "gfedcba";
    std::sort(str.begin(), str.end());
    BOOST_CHECK( str == "abcdefg" );
    
    // Oven range-based
    str = "gfedcba";
    oven::sort(str);
    BOOST_CHECK( str == "abcdefg" );
}


void test_copied()
{
    std::vector<int> vec = oven::make_counting_range(3, 9)|copied;
    vec.push_back(9);
    BOOST_CHECK( oven::equals(vec, oven::make_counting_range(3, 10)) );
}


void test_distance()
{
    std::string str("012345");
    BOOST_CHECK( oven::distance(str) == 6 );
}


void test_equals()
{
    std::string str("hello, equals");
    std::vector<char> vec = str|copied;
    BOOST_CHECK( oven::equals(str, vec) );
}


#include <boost/array.hpp>

void test_array_range()
{
    std::string str("hello, array_range!");
    boost::array<char, 19> sarr;
    str|copied(sarr);
    oven::array_range<char> darr(19);
    str|copied(darr);

    BOOST_CHECK( oven::equals(sarr, darr) );
}


void test_counting_range()
{
    int ints[] = { 2, 3, 4, 5, 6 };
    BOOST_CHECK( oven::equal(oven::make_counting_range(2, 7), ints) );
}


void test_directory_range()
{

}


void test_empty_range()
{
    BOOST_CHECK( boost::empty(empty_range<int>()) );
}


void test_file_range()
{

}


#include <iterator>

void test_istream_range()
{
    std::string src("hello,istream_range!");

    std::stringstream ss;
    ss << src;

    std::string result;
    oven::copy(oven::make_istream_range<char>(ss), std::back_inserter(result));

    BOOST_CHECK( oven::equals(result, src) );
}


void test_single_range()
{
    BOOST_CHECK( oven::equals(oven::make_single_range('a'), std::string("a")) );
}


struct not_divisor
{
    bool operator()(int x, int y) const
    { return (y % x) != 0; }
};

void test_adjacent_filtered()
{
    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int answer[] = { 2, 6, 8, 10, 120 };

    BOOST_CHECK( oven::equals(
        src|adjacent_filtered(::not_divisor()),
        answer
    ) );
}



void test_appended()
{
    std::string const str("hello, appen");

    BOOST_CHECK( oven::equals(
        str|appended('d')|appended('e')|appended('d')|appended('!'),
        std::string("hello, appended!")
    ) );
}


struct find
{
    typedef char result_type;

    char operator()(char ch) const
    {
        return std::toupper(ch, std::locale());
    }
};


void test_applied()
{

}


void test_array_protected()
{

}


void test_checked()
{
    std::string in("012345");
    std::string out("01234");

    try {
        oven::copy(in, boost::begin(out|checked));
    }
    catch (check_error const& ) {
        return;
    }

    BOOST_CHECK(false);
}


void test_cleared()
{
    BOOST_CHECK( boost::empty(
        std::string("labor")
            | jointed(std::string("lost"))
            | cleared
    ) );
}


#include <vector>
#include <list>

void test_jointed()
{
    std::string str0("every range");
    std::vector<char> str1 = std::string(" is")|copied;
    std::list<char> str2 = std::string(" string!?")|copied;

    BOOST_CHECK( oven::equals(
        str0|jointed(str1)|jointed(str2),
        std::string("every range is string!?")
    ) );
}


void test_constants()
{
    BOOST_CHECK( oven::equals(
        std::string("labor")
            | jointed(std::string("will be"))
            | constants("lost"),
        std::string("lost")
    ) );
}


void test_copied_as_adaptor()
{
    using namespace boost;

    std::string src("axaxaxbxbxbx");
    std::string snapshot;
    std::string answer("bbb");

    BOOST_CHECK( oven::equals(
        src
            | filtered(lambda::_1 != 'x')
            | copied(std::back_inserter(snapshot))
            | filtered(lambda::_1 != 'a'),
        answer
    ) );

    BOOST_CHECK( snapshot == "aaabbb" );
}


int test_main(int, char*[])
{
    ::test_introduction();

    ::test_stl_algorithms();
    ::test_copied();
    ::test_distance();
    ::test_equals();

    ::test_array_range();
    ::test_counting_range();
    ::test_directory_range();
    ::test_empty_range();
    ::test_istream_range();
    ::test_single_range();

    ::test_adjacent_filtered();
    ::test_appended();
    ::test_applied();
    ::test_array_protected();
    ::test_checked();
    ::test_cleared();
    ::test_constants();
    ::test_copied_as_adaptor();

    ::test_jointed();

    return 0;
}
