#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUSE_HPP
#define PSTADE_FUSE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/at.hpp>
#include <pstade/callable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unused.hpp>


namespace pstade {


    namespace fuse_detail {


        using boost::mpl::int_;


        template< class Tuple >
        struct result_of_size :
            int_<
                boost::tuples::length<
                    typename boost::remove_cv<Tuple>::type // Boost.Tuple needs 'remove_cv'.
                >::value
            >
        { };


        template< class Function, class FusionSeq, class Arity >
        struct apply_impl;


        // 0ary

        template< class Function, class FusionSeq >
        struct apply_impl< Function, FusionSeq, int_<0> > :
            boost::result_of< Function(
            ) >
        { };

        template< class Result, class Function, class FusionSeq > inline
        Result call_impl(Function const& fun, FusionSeq& seq, int_<0>)
        {
            pstade::unused(seq);
            return fun(
            );
        }


        // 1ary-

    #define PSTADE_max_arity 10
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/fuse.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity


        template< class Function >
        struct op_result :
            callable< op_result<Function> >
        {
            template< class Myself, class FusionSeq >
            struct apply
            {
                typedef typename result_of_size<FusionSeq>::type n_t;
                typedef typename apply_impl<Function, FusionSeq, n_t>::type type;
            };

            template< class Result, class FusionSeq >
            Result call(FusionSeq& seq) const
            {
                typedef typename result_of_size<FusionSeq>::type n_t;
                return fuse_detail::call_impl<Result>(m_fun, seq, n_t());
            }

            explicit op_result() // for ForwardIterator
            { }

            explicit op_result(Function const& fun) :
                m_fun(fun)
            { }

            typedef Function base_type;

            Function const& base()
            {
                return m_fun;
            }

        private:
            Function m_fun;
        };


    } // namespace fuse_detail


    PSTADE_OBJECT_GENERATOR(fuse, (fuse_detail::op_result< deduce<_1, to_value> >))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Function, class FusionSeq >
struct apply_impl< Function, FusionSeq, int_< n > > :
    boost::result_of< Function(
        PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::result_of<op_at_c<PSTADE_PP_INT, >(FusionSeq&)>::type)
    ) >
{ };

template< class Result, class Function, class FusionSeq > inline
Result call_impl(Function const& fun, FusionSeq& seq, int_< n >)
{
    return fun(
        PSTADE_PP_ENUM_PARAMS_WITH(n, pstade::at_c<PSTADE_PP_INT, >(seq))
    );
}


#undef n
#endif
