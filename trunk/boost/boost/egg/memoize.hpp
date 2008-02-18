#ifndef BOOST_EGG_MEMOIZE_HPP
#define BOOST_EGG_MEMOIZE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.kmonos.net/wlog/52.php
// http://d.hatena.ne.jp/Cryolite/20050902#p1


#include <map>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/egg/by_cref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/fix.hpp>
#include <boost/egg/function_facade.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    namespace memoize_detail {


        struct wrap_ :
            function_facade<wrap_, by_cref>
        {
            template<class Me, class Base, class Fixed, class Arg>
            struct apply :
                result_of<
                    typename result_of<Base(Fixed const &)>::type(Arg const &)
                >
            { };

            template<class Re, class Base, class Fixed, class Arg>
            Re call(Base &base, Fixed &fixed, Arg const &arg) const
            {
                typedef std::map<Arg, Re> map_t;

                if (m_pany->empty())
                    *m_pany = map_t();

                map_t &m = boost::any_cast<map_t &>(*m_pany);

                typename map_t::iterator it = m.find(arg);
                if (it != m.end())
                    return it->second;
                else
                    return m[arg] = base(fixed)(arg);
            }

            wrap_() :
                m_pany(new any())
            { }

        private:
            shared_ptr<any> m_pany;
        };


        struct little
        {
            template<class Me, class Base_>
            struct apply :
                result_of<
                    T_fix(
                        typename result_of<
                            typename result_of<T_curry3(wrap_)>::type(typename result_of<T_curry2(Base_ &)>::type)
                        >::type
                    )
                >
            { };

            template<class Re, class Base_>
            Re call(Base_ base) const
            {
                return fix(
                    curry3(wrap_())(curry2(base))
                );
            }
        };


    } // namespace memoize_detail


    typedef function<memoize_detail::little, by_value> T_memoize;
    BOOST_EGG_CONST((T_memoize), memoize) = {{}};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
