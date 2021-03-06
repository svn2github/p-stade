#ifndef PSTADE_LIME_NODE_HPP
#define PSTADE_LIME_NODE_HPP


// PStade.Lime
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <map>
#include <string>
#include <boost/foreach.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>
#include <boost/optional.hpp>
#include <boost/range/empty.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/sequence_cast.hpp>
#include <pstade/overload.hpp>
#include <pstade/unused.hpp>
#include <pstade/ustring.hpp>
#include <pstade/what.hpp>
#include "./detail/node_fwd.hpp"
#include "./error.hpp"
#include "./new_node.hpp"


namespace pstade { namespace lime {


struct node_not_found :
    error
{
    explicit node_not_found(std::string what) :
        error(what)
    { }
};


namespace node_detail {


    inline
    void throw_error(ustring name)
    {
        node_not_found err(pstade::what("<node-not-found>", name));
        boost::throw_exception(err);
    }


} // namesapce node_detail


struct default_interface
{ };


template<
    class Interface = default_interface
>
struct node :
    Interface,
    boost::ptr_list< node<Interface> >,
    private boost::noncopyable
{
    typedef std::map<ustring, ustring> attributes_type;

public:
    // structors
    //
    virtual ~node()
    { }

    // accessors
    //
    boost::optional<node&> parent() const
    {
        return m_parent;
    }

    ustring name() const
    {
        return m_name;
    }

    attributes_type& attributes()
    {
        return m_atts;
    }

    node& child(ustring childName)
    {
        return get_child(childName);
    }

    ustring& att(ustring attName)
    {
        return m_atts[attName];
    }

    // syntax sugars
    //
    node& operator/(ustring childName)
    {
        return child(childName);
    }

    ustring& operator%(ustring attName)
    {
        return att(attName);
    }

    node& operator+=(ustring childName)
    {
        this->push_back(lime::new_node(*this, childName));
        return *this;
    }

// private:
    void detail_construct(node& parent, ustring name)
    {
        m_parent = parent;
        m_name = name;
    }

private:
    boost::optional<node&> m_parent;
    ustring m_name;
    attributes_type m_atts;

    node& get_child(ustring childName)
    {
        node& self(*this); // VC++ workaround

        BOOST_FOREACH (node& child, self) {
            if (oven::equals(child.name(), childName))
                return child;
        }

        // Question:
        //   better? maybe not.
        //
        // node *baby = new node(childName);
        // push_back(baby);
        // return *baby;

        node_detail::throw_error(childName);
        return *this; // suppress warning
    }
};


} } // namespace pstade::lime


inline
pstade::lime::node<pstade::lime::default_interface> *
pstade_lime_new_node(
    pstade::lime::node<pstade::lime::default_interface>& parent,
    pstade::ustring childName,
    pstade::overload)
{
    using namespace pstade::lime;

    pstade::unused(parent, childName);
    return new node<default_interface>();
}


#endif
