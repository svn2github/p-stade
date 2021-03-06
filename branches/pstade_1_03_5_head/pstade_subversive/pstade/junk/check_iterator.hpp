#ifndef PSTADE_OVEN_CHECK_ITERATOR_HPP
#define PSTADE_OVEN_CHECK_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: 'stdext::checked_iterator'
//
// http://msdn2.microsoft.com/en-us/library/at797xz3.aspx


#include <stdexcept> // logic_error, out_of_range
#include <string>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/object_generator.hpp>


namespace pstade { namespace oven {


template< class Iterator >
struct check_iterator;


struct singular_iterator_operation :
    std::logic_error
{
    explicit singular_iterator_operation(std::string const& msg) :
        std::logic_error(msg)
    { }
};

struct incompatible_iterators :
    std::logic_error
{
    explicit incompatible_iterators(std::string const& msg) :
        std::logic_error(msg)
    { }
};


namespace check_iterator_detail {


    template< class Iterator >
    struct super_
    {
        typedef
            boost::iterator_adaptor<
                check_iterator<Iterator>,
                Iterator
            >
        type;
    };


    inline
    void throw_out_of_range()
    {
        std::out_of_range err("out of 'check_iterator' range");
        boost::throw_exception(err);
    }


    template< class CheckIterator >
    void check_singularity(CheckIterator const& it)
    {
        if (it.is_singular()) {
            singular_iterator_operation err("operation on default-constructed 'check_iterator'");
            boost::throw_exception(err);
        }
    }


    template< class CheckIterator, class CheckIterator_ >
    void check_compatibility(CheckIterator const& it, CheckIterator_ const& it_)
    {
        if (it.begin() != it_.begin() || it.end() != it_.end()) {
            incompatible_iterators err("incompatible iterators of 'check_iterator'");
            boost::throw_exception(err);
        }
    }


} // namespace check_iterator_detail


template< class Iterator >
struct check_iterator :
    check_iterator_detail::super_<Iterator>::type
{
private:
    typedef typename check_iterator_detail::super_<Iterator>::type super_t;
    typedef typename super_t::reference ref_t;
    typedef typename super_t::difference_type diff_t;

public:
    check_iterator() :
        m_singular(true)
    { }

    check_iterator(Iterator const& it, Iterator const& first, Iterator const& last) :
        super_t(it),
        m_first(first), m_last(last),
        m_singular(false)
    { }

    template< class I >
    check_iterator(check_iterator<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()),
        m_first(other.begin()), m_last(other.end()),
        m_singular(other.is_singular())
    {
        check_iterator_detail::check_singularity(*this);
    }

    Iterator const& begin() const
    {
        check_iterator_detail::check_singularity(*this);
        return m_first;
    }

    Iterator const& end() const
    {
        check_iterator_detail::check_singularity(*this);
        return m_last;
    }

    bool is_begin() const
    {
        check_iterator_detail::check_singularity(*this);
        return this->base() == m_first;
    }

    bool is_end() const
    {
        check_iterator_detail::check_singularity(*this);
        return this->base() == m_last;
    }

    bool is_singular() const
    {
        return m_singular;
    }

private:
    Iterator m_first, m_last;
    bool m_singular;

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        check_iterator_detail::check_singularity(*this);

        if (is_end())
            check_iterator_detail::throw_out_of_range();

        return *this->base();
    }

    template< class I >
    bool equal(check_iterator<I> const& other) const
    {
        check_iterator_detail::check_singularity(*this);
        check_iterator_detail::check_singularity(other);
        check_iterator_detail::check_compatibility(*this, other);

        return this->base() == other.base();
    }

    void increment()
    {
        check_iterator_detail::check_singularity(*this);

        if (is_end())
            check_iterator_detail::throw_out_of_range();

        ++this->base_reference();
    }

    void decrement()
    {
        check_iterator_detail::check_singularity(*this);

        if (is_begin())
            check_iterator_detail::throw_out_of_range();

        --this->base_reference();
    }

    void advance(diff_t const& d)
    {
        check_iterator_detail::check_singularity(*this);

        if (
            ( d >= 0 &&  d > ( m_last - this->base()  ) ) ||
            ( d <  0 && -d > ( this->base() - m_first ) )
        ) {
            check_iterator_detail::throw_out_of_range();
        }

        this->base_reference() += d;
    }

    template< class I >
    diff_t distance_to(check_iterator<I> const& other) const
    {
        check_iterator_detail::check_singularity(*this);
        check_iterator_detail::check_singularity(other);
        check_iterator_detail::check_compatibility(*this, other);

        return other.base() - this->base();
    }
};


PSTADE_OBJECT_GENERATOR(make_check_iterator,
    (check_iterator< deduce<_1, to_value> >) const)


} } // namespace pstade::oven


#endif
