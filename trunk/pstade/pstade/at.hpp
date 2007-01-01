#ifndef PSTADE_AT_HPP
#define PSTADE_AT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Provides Boost.Fusion-like interfaces to Boost.Tuple.
// 'value_at', whose funny name comes from Boost.Fusion,
// can return reference type.
// Note that 'std::pair' can't hold reference type
// because of the reference-to-reference problem.


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/affect.hpp>
#include <pstade/apple/pair_fwd.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    // at_first/second


    template<class Pair>
    struct value_at_first
    {
        typedef typename Pair::first_type type;
    };


    template<class Pair>
    struct value_at_second
    {
        typedef typename Pair::second_type type;
    };


    struct op_at_first :
        callable<op_at_first>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename value_at_first<Pair>::type>
        { };

        template<class Result, class Pair>
        Result call(Pair& p) const
        {
            return p.first;
        }
    };

    PSTADE_CONSTANT(at_first, (op_at_first))


    struct op_at_second :
        callable<op_at_second>
    {
        template<class Myself, class Pair>
        struct apply :
            affect<Pair&, typename value_at_second<Pair>::type>
        { };

        template<class Result, class Pair>
        Result call(Pair& p) const
        {
            return p.second;
        }
    };

    PSTADE_CONSTANT(at_second, (op_at_second))


    // at


    template<class Tuple, class N>
    struct value_at :
        boost::tuples::element<N::value, typename boost::remove_cv<Tuple>::type>
    { };


    template<class N>
    struct op_at :
        callable<op_at<N> >
    {
        template<class Myself, class Tuple>
        struct apply :
            affect<Tuple&, typename value_at<Tuple, N>::type>
        { };

        template<class Result, class Tuple>
        Result call(Tuple& t) const
        {
            return boost::tuples::get<N::value>(t);
        }
    };


    template<class N, class Tuple> inline
    typename const_overloaded_eval_result<
        boost::result_of<op_at<N>(Tuple&)>, Tuple
    >::type
    at(Tuple& t)
    {
        return op_at<N>()(t);
    }

    template<class N, class Tuple> inline
    typename boost::result_of<op_at<N>(Tuple const&)>::type
    at(Tuple const& t)
    {
        return op_at<N>()(t);
    }


} // namespace pstade


#endif
