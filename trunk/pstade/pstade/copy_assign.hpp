#ifndef PSTADE_COPY_ASSIGN_HPP
#define PSTADE_COPY_ASSIGN_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Lets "./automatic.hpp" work with 'operator='.


#include <pstade/function.hpp>


namespace pstade {


    namespace copy_assign_detail {


        template<class To, class From>
        struct baby
        {
            typedef To& result_type;

            result_type operator()(To& to, From& from) const
            {
                to.operator=(static_cast<To const&>(from));
                return to;
            }
        };


    } // namespace copy_assign_detail


    PSTADE_FUNCTION(copy_assign, (copy_assign_detail::baby<_, _>))


} // namespace pstade


#endif
