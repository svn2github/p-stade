int ans[] = { 2, 3, 4, 5, 6 };
BOOST_CHECK( oven::equal(oven::make_count_range(2, 7), ans) );

std::vector<int> vec;
BOOST_FOREACH (int i, oven::count_to(5)) {
    vec.push_back(i);
}