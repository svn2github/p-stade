#ifndef PSTADE_OVEN_ANY_ITERATOR_HPP
#define PSTADE_OVEN_ANY_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// Is it possible to support OutputIterator?


#include <cstddef> // ptrdiff_t
#include <boost/any.hpp>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // tags
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <pstade/clone_ptr.hpp>
#include <pstade/new.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven {


template<
    class Value,
    class Traversal,
    class Reference,
    class Difference
>
struct any_iterator;


namespace any_iterator_detail {


    template<
        class Reference,
        class Difference
    >
    struct placeholder :
        private boost::noncopyable
    {
        virtual Reference dereference() const = 0;
        virtual bool equal(placeholder const& other) const = 0;
        virtual void increment() = 0;
        virtual void decrement() = 0;
        virtual void advance(Difference d) = 0;
        virtual Difference difference_to(placeholder const& other) const = 0;

        virtual placeholder *clone() const = 0;
        virtual boost::any base() const = 0;
        virtual ~placeholder() { }
    };


    // Topic:
    // You can't use the friend-injection to 'placeholder' here.
    // Consider null 'clone_ptr'.
    // As it doesn't require any instance of 'placeholder',
    // there is no instantiation of 'new_clone' for 'placeholder'.
    // Thus copy-constructor of 'clone_ptr' would fail to find 'new_clone'.
    template< class Reference, class Difference > inline
    placeholder<Reference, Difference> *
    new_clone(placeholder<Reference, Difference> const& ph)
    {
        return ph.clone();
    }


    template< class Iterator >
    void decrement_aux(Iterator& it, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(it);
    }

    template< class Iterator >
    void decrement_aux(Iterator& it, boost::bidirectional_traversal_tag)
    {
        --it;
    }


    template< class Iterator, class Difference >
    void advance_aux(Iterator& it, Difference d, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(it, d);
    }

    template< class Iterator, class Difference >
    void advance_aux(Iterator& it, Difference d, boost::random_access_traversal_tag)
    {
        it += d;
    }


    template< class Difference, class Iterator >
    Difference difference_to_aux(Iterator const& first, Iterator const& last, boost::single_pass_traversal_tag)
    {
        BOOST_ASSERT(false);
        pstade::unused(first, last);
        return Difference();
    }

    template< class Difference, class Iterator >
    Difference difference_to_aux(Iterator const &first, Iterator const& last, boost::random_access_traversal_tag)
    {
        return last - first;
    }


    template<
        class Iterator,
        class Traversal,
        class Reference,
        class Difference
    >
    struct holder :
        placeholder<Reference, Difference>
    {
    private:
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_traversal<Iterator>::type,  Traversal>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_reference<Iterator>::type,  Reference>));
        BOOST_MPL_ASSERT((boost::is_convertible<typename boost::iterator_difference<Iterator>::type, Difference>));

        typedef holder self_t;
        typedef placeholder<Reference, Difference> placeholder_t;

    public:
        explicit holder(Iterator const& held) :
          m_held(held)
        { }

    public: 
        virtual Reference dereference() const
        {
            return *m_held;
        }

        virtual bool equal(placeholder_t const& other) const
        {
        #if defined(NDEBUG)
            return m_held == static_cast<self_t const&>(other).m_held;
        #else
            self_t const& other_ = dynamic_cast<self_t const&>(other);
            return m_held == other_.m_held;
        #endif
        }

        virtual void increment()
        {
            ++m_held;
        }

        virtual void decrement()
        {
            any_iterator_detail::decrement_aux(m_held, Traversal());
        }

        virtual void advance(Difference d)
        {
            any_iterator_detail::advance_aux(m_held, d, Traversal());
        }

        virtual Difference difference_to(placeholder_t const& other) const
        {
            return any_iterator_detail::difference_to_aux<Difference>(
                m_held, static_cast<self_t const&>(other).m_held, Traversal());
        }

    public:
        virtual boost::any base() const
        {
            return m_held;
        }

    private:
        virtual placeholder_t *clone() const
        {
            return new self_t(m_held);
        }

    private:
        Iterator m_held;
    };


    template<
        class Value,
        class Traversal,
        class Reference,
        class Difference
    >
    struct super_
    {
        typedef boost::iterator_facade<
            any_iterator<Value, Traversal, Reference, Difference>,
            Value,
            Traversal,
            Reference,
            Difference
        > type;
    };


} // namespace any_iterator_detail


template<
    class Value,
    class Traversal,
    class Reference  = Value&,
    class Difference = std::ptrdiff_t
>
struct any_iterator :
    any_iterator_detail::super_<Value, Traversal, Reference, Difference>::type
{
private:
    typedef any_iterator self_t;
    typedef typename any_iterator_detail::super_<Value, Traversal, Reference, Difference>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;
    typedef any_iterator_detail::placeholder<Reference, Difference> placeholder_t;

public:
    explicit any_iterator()
    { }

    // 'explicit' must be required.
    // There is no way to know the convertibility before instantiation.
    template< class Iterator >
    explicit any_iterator(Iterator const& it) :
        m_pimpl(pstade::new_< any_iterator_detail::holder<
            Iterator,
            Traversal, Reference, Difference
        > >(it))
    { }

#if 0 // impossible
    // This class is convertible only to the same type,
    // because 'holder::equals/difference_to' requires the same 'holder' type.
    template< class Value_, class Traversal_, class Reference_, class Difference_ >
    any_iterator(any_iterator<Value_, Traversal_, Reference_, Difference_> const& other,
        typename boost::enable_if_convertible<Traversal_,  Traversal>::type  * = 0,
        typename boost::enable_if_convertible<Reference_,  Reference>::type  * = 0,
        typename boost::enable_if_convertible<Difference_, Difference>::type * = 0
    ) :
        m_pimpl(pstade::new_< any_iterator_detail::holder<
            any_iterator<Value_, Traversal_, Reference_, Difference_>,
            Traversal, Reference, Difference
        > >(other))
    { }
#endif

    boost::any base() const
    {
        return m_pimpl->base();
    }

private:
    clone_ptr<placeholder_t> m_pimpl;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_pimpl->dereference();
    }

    bool equal(self_t const& other) const
    {
        return m_pimpl->equal(*other.m_pimpl);
    }

    void increment()
    {
        m_pimpl->increment();
    }

    void decrement()
    {
        m_pimpl->decrement();
    }

    void advance(diff_t d)
    {
        m_pimpl->advance(d);
    }

    diff_t distance_to(self_t const& other) const
    {
        return m_pimpl->difference_to(*other.m_pimpl);
    }
};


} } // namespace pstade::oven


#endif
