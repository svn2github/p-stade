using boost::assign::list_of;
using boost::lambda::_1;
using namespace pstade::oven;

typedef
    any_range<int, boost::single_pass_traversal_tag, int>
range;

range denominators(int x)
{
    return counting(1, x+1)|filtered(x % _1 == 0)|regularized;
}

bool is_prime(int x)
{
    return equals(denominators(x), list_of(1)(x));
}

range primes =
    iteration(1, _1 + 1)|regularized|filtered(&is_prime);

pstade::op_lexical_cast<std::string> to_string;

int main()
{
    BOOST_FOREACH (std::string p, primes|taken(500)|transformed(to_string))
        std::cout << p << ',';
}