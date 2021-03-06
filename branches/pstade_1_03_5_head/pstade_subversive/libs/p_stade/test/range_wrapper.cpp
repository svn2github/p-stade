#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


#include <boost/range.hpp>
#include <boost/iterator/permutation_iterator.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/utility/result_of.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/add_const.hpp>


template<class A>
struct detail_argument :
    boost::remove_reference<
        typename boost::add_const<A>::type
    >
{ };


struct op_make_permuted
{
    template<class FunCall>
    struct result { };

    template<class Fun, class Elements, class Indices>
    struct result<Fun(Elements, Indices)>
    {
        typedef
            boost::permutation_iterator<
                typename boost::range_result_iterator<
                    typename detail_argument<Elements>::type
                >::type,
                typename boost::range_const_iterator<
                    typename detail_argument<Indices>::type
                >::type
            >
        iter_t;

        typedef
            boost::iterator_range<iter_t> const
        type;
    };

    template<class Elements, class Indices>
    typename result<void(Elements&, Indices&)>::type
    aux(Elements& es, Indices& is) const
    {
        typedef result<void(Elements&, Indices&)> result_;
        return typename result_::type(
            typename result_::iter_t(boost::begin(es), boost::begin(is)),
            typename result_::iter_t(boost::begin(es), boost::end(is))
        );
    }

    template<class Elements, class Indices>
    typename result<void(Elements&, Indices const&)>::type
    operator()(Elements& es, Indices const& is) const
    {
        return aux(es, is);
    }

    template<class Elements, class Indices>
    typename result<void(Elements const&, Indices const&)>::type
    operator()(Elements const& es, Indices const& is) const
    {
        return aux(es, is);
    }
};

namespace { op_make_permuted const make_permuted = { }; }


void test()
{
    std::string es("abcdefghijklmn");
    int is[] = { 3, 8, 5, 1 };

    boost::result_of< ::op_make_permuted(std::string&, int(&)[4]) >::type
        result = ::make_permuted(es, is);
    BOOST_CHECK( boost::equals(result, std::string("difb")) );
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}