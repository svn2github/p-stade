#include <pstade/vodka/drink.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// ASCII file only.
// newline character must be '\n'.
// tabsize is 4.


#include <pstade/oven.hpp>


#include <exception>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <boost/cstdint.hpp>
#include <boost/foreach.hpp>
#include <pstade/oven.hpp>
#include <pstade/wine.hpp>


using namespace pstade;


void expand_tab(std::string fileName)
{
    std::vector<boost::uint8_t> buf =
        oven::file_range<boost::uint8_t>(fileName)
            | pstade::required("non-empty input file: " + fileName)
            | oven::tab_expanded(4)
            | oven::copied;

    std::ofstream fout(fileName.c_str(), std::ios::binary);
    pstade::require(fout, "good output file: " + fileName);
    oven::copy(buf, oven::applier(oven::stream_output(fout)));
};


int main(int argc, char *argv[])
{
    BOOST_FOREACH (int i, oven::count_from_to(1, argc)) {

        try {
            ::expand_tab(argv[i]);
        }
        catch (std::exception& err) {
            std::cout << err.what() << std::endl;
        }

    }

    return 0; // std::cout << "<press-any-key/>", pstade::pause();
}
