#ifndef PSTADE_INVARIANT_HPP
#define PSTADE_INVARIANT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>


namespace pstade {


#if !defined(NDEBUG)


struct invariant :
    private boost::noncopyable
{
    // friend
    //
    class access
    {
    public:
        template< class T >
        static bool detail_check(T& x)
        {
            return x.pstade_invariant();
        }
    };

    template< class T >
    static bool holds(T& x)
    {
        return access::detail_check(x);
    }

private:
    // type erasure
    //
    struct placeholder
    {
        virtual bool check() const = 0;
        virtual ~placeholder() { }
    };

    template< class T >
    struct holder :
        placeholder
    {
        explicit holder(T& x) :
            m_x(x)
        { }

        virtual bool check() const
        {
            return access::detail_check(m_x);
        }

        T& m_x;
    };

public:
    // ctor/dtor
    //
    template< class T >
    explicit invariant(T& x) :
        m_px(new holder<T>(x))
    {
        BOOST_ASSERT(m_px->check());
    }

    ~invariant()
    {
        BOOST_ASSERT(m_px->check());
    }

private:
    boost::scoped_ptr<placeholder> m_px;
};


#else


struct invariant :
    private boost::noncopyable
{
    class access
    { };

    template< class T >
    static bool holds(T& )
    {
        return true;
    }

    template< class T >
    explicit invariant(T& )
    { }
};


#endif // !defined(NDEBUG)


} // namespace pstade


#endif
