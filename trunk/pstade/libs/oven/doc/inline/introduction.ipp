typedef any_range<int> range;

range sieve(range rng)
{
    return rng|dropped(1)|filtered(regular(lambda::_1 % front(rng) != 0));
}

range primes = iteration(range(counting_from(2)), &::sieve)|transformed(front);

int main()
{
    std::cout << (primes|taken(500));
}
