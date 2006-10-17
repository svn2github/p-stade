#ifndef PSTADE_OVEN_GENERATE_ITERATOR_HPP
#define PSTADE_OVEN_GENERATE_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/indirect_reference.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/optional.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven {


template< class Generator >
struct generate_iterator;


namespace generate_iterator_detail {


    template< class Generator >
    struct generator_result :
        boost::result_of<typename remove_cvr<Generator>::type()>
    { };


    template< class T >
    struct indirect_reference :
        boost::indirect_reference<T>
    { };

    template< class T >
    struct indirect_reference< boost::optional<T> > :
        boost::add_reference<T>
    { };


    template< class Generator >
    struct aux_gen
    {
        explicit aux_gen(Generator const& gen) :
            m_gen(gen)
        { }

        template< class Result >
        Result call()
        {
            return m_gen();
        }

    private:
        Generator m_gen;
    };

    template< class Generator >
    struct aux_gen< Generator& >
    {
        explicit aux_gen(Generator& gen) :
            m_pgen(boost::addressof(gen))
        { }

        template< class Result >
        Result call()
        {
            return (*m_pgen)();
        }

    private:
        Generator *m_pgen; // be a pointer for Assignable.
    };


    template< class Generator >
    struct super_
    {
        typedef typename generator_result<Generator>::type result_t;
        typedef typename indirect_reference<result_t>::type ref_t;
        typedef typename remove_cvr<ref_t>::type val_t;

        typedef boost::iterator_facade<
            generate_iterator<Generator>,
            val_t,
            boost::single_pass_traversal_tag,
            ref_t            
        > type;
    };


} // namespace generate_iterator_detail


template< class Generator >
struct generate_iterator :
    generate_iterator_detail::super_<Generator>::type
{
private:
    typedef generate_iterator self_t;
    typedef typename generate_iterator_detail::super_<Generator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef generate_iterator_detail::aux_gen<Generator> aux_gen_t;
    typedef typename generate_iterator_detail::generator_result<Generator>::type result_t;

public:
    // This requires non-reference Generator to be
    // DefaultConstructible, but SinglePassIterator is not
    // required to be DefaultConstructible.
    // generate_iterator()
    // { }

    generate_iterator(Generator gen, bool not_end) :
        m_gen(gen),
        m_result() // can be a pointer, so value-initialize it.
    {
        if (not_end)
            generate();
    }

    bool is_end() const
    {
        return !m_result;
    }

private:
    aux_gen_t m_gen;
    mutable result_t m_result;

    void generate()
    {
        m_result = m_gen.template call<result_t>();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return *m_result;
    }

    bool equal(self_t const& other) const
    {
        return is_end() && other.is_end();
    }

    void increment()
    {
        BOOST_ASSERT(!is_end());
        generate();
    }
};


template< class Generator >
generate_iterator<Generator> const
make_generate_iterator(Generator gen, bool not_end)
{
    return generate_iterator<Generator>(gen, not_end);
}


} } // namespace pstade::oven


#endif
