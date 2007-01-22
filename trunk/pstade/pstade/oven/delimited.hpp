#ifndef PSTADE_OVEN_DELIMITED_HPP
#define PSTADE_OVEN_DELIMITED_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include "./concatenated.hpp"
#include "./concepts.hpp"
#include "./jointed.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace delimited_detail {


    template< class Delimiter >
    struct with :
        callable< with<Delimiter> >
    {
        template< class Myself, class LocalRange >
        struct apply :
            boost::result_of<
                op_make_jointed(Delimiter&, LocalRange&)
            >
        { };

        template< class Result, class LocalRange >
        Result call(LocalRange& local) const
        {
            return make_jointed(*m_pdelim, local);
        }

        explicit with()
        { }

        explicit with(Delimiter& delim) :
            m_pdelim(boost::addressof(delim))
        { }

    private:
        Delimiter *m_pdelim;
    };


    template< class SegmentRange, class Delimiter >
    struct baby
    {
        typedef
            typename boost::result_of<
                op_make_concatenated(
                    typename boost::result_of<
                        op_make_transformed<>(SegmentRange&, with<Delimiter>)
                    >::type
                )
            >::type
        result;

        result call(SegmentRange& rngs, Delimiter& delim)
        {
            PSTADE_CONCEPT_ASSERT((SinglePass<SegmentRange>));
            PSTADE_CONCEPT_ASSERT((SinglePass<Delimiter>));

            return make_concatenated(
                make_transformed(rngs, with<Delimiter>(delim))
            );
        }
    };


} // namespace delimited_detail


PSTADE_FUNCTION(make_delimited, (delimited_detail::baby<_, _>))
PSTADE_PIPABLE(delimited, (op_make_delimited))


} } // namespace pstade::oven


#endif