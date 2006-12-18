#ifndef PSTADE_OVEN_COMPILE_HPP
#define PSTADE_OVEN_COMPILE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/xpressive/proto/compile.hpp>
#include <boost/xpressive/proto/operators.hpp>
#include <pstade/callable.hpp>
#include <pstade/const.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./joint_iterator.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


    namespace compile_detail {


        template< class RangeL, class RangeR >
        struct copied_joint_range_super :
            iter_range<
                joint_iterator<
                    typename range_iterator<RangeL>::type,
                    typename range_iterator<RangeR>::type
                >
            >
        { };

        template< class RangeL, class RangeR >
        struct copied_joint_range :
            copied_joint_range_super<RangeL, RangeR>::type,
            private as_lightweight_proxy< copied_joint_range<RangeL, RangeR> >
        {
        private:
            typedef typename copied_joint_range_super<RangeL, RangeR>::type super_t;

        public:
            copied_joint_range(RangeL rngL, RangeR rngR) : // copy them!!
                super_t(
                    oven::make_joint_left_iterator(boost::begin(rngL), boost::end(rngL), boost::begin(rngR)),
                    oven::make_joint_right_iterator(boost::end(rngL), boost::begin(rngR), boost::end(rngR))
                )
            { }
        };

        namespace proto = boost::proto;


        struct oven_tag  { };
        struct state_t   { };
        struct visitor_t { };


        struct joint_compiler
        {
            template< class Expr, class State, class Visitor >
            struct apply
            {
                typedef typename Expr::arg0_type::expr_type left_type;
                typedef typename Expr::arg1_type::expr_type right_type;

                // compile the left branch
                typedef typename
                    proto::compiler<typename left_type::tag_type,  oven_tag>::template apply<left_type,  State, Visitor>::type
                left_compiled_type;

                // compile the right branch
                typedef typename
                    proto::compiler<typename right_type::tag_type, oven_tag>::template apply<right_type, State, Visitor>::type
                right_compiled_type;

                typedef
                    copied_joint_range<left_compiled_type, right_compiled_type> const
                type;
            };

            template< class Expr, class State, class Visitor >
            static typename apply<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                return typename apply<Expr, State, Visitor>::type(
                    proto::compile(proto::left(expr),  state, visitor, oven_tag()),
                    proto::compile(proto::right(expr), state, visitor, oven_tag())
                );
            }
        };


        struct terminal_compiler
        {
            template< class Expr, class State, class Visitor >
            struct apply :
                sub_range_result<PSTADE_CONST(typename Expr::arg0_type)> // for *copied*_joint_range
            { };

            template< class Expr, class State, class Visitor >
            static typename apply<Expr, State, Visitor>::type
            call(Expr const& expr, State const& state, Visitor& visitor)
            {
                pstade::unused(state, visitor);
                return proto::arg(expr);
            }
        };


        struct op :
            callable<op>
        {
            template< class Myself, class Xpr >
            struct apply :
                boost::proto::meta::compile<Xpr, state_t,  visitor_t, oven_tag>
            { };

            template< class Result, class Xpr >
            Result call(Xpr& xpr) const
            {
                state_t state;
                visitor_t visitor;
                return proto::compile(xpr, state, visitor, oven_tag());
            }
        };


    } // namespace compile_detail


    typedef compile_detail::op op_compile;
    PSTADE_CONSTANT(compile, (op_compile))
    PSTADE_PIPABLE(compiled, (op_compile))


    struct op_as_expr :
        callable<op_as_expr>
    {
        template< class Myself, class Range >
        struct apply :
            boost::proto::meta::terminal<Range>
        { };

        template< class Result, class Range >
        Result call(Range& rng) const
        {
            return boost::proto::make_terminal(rng);
        }
    };


    PSTADE_CONSTANT(as_expr, (op_as_expr))


} } // namespace pstade::oven


namespace boost { namespace proto {


    template< >
    struct compiler<tag::add, pstade::oven::compile_detail::oven_tag> :
        pstade::oven::compile_detail::joint_compiler
    { };

    template< >
    struct compiler<tag::terminal, pstade::oven::compile_detail::oven_tag> :
        pstade::oven::compile_detail::terminal_compiler
    { };


} } // namespace boost::proto


#endif
