#include "iterator.h"
#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <algorithm>

TEST(TEST_ITERAOTR, TEST_INSERTITERATOR)
{
    std::vector<int> v{1, 2, 3, 4, 5};
    std::list<int> l{-1, -2, -3};
    int sz_ori = l.size();

    std::copy(v.begin(), v.end(),
              xtl::inserter_iterator<std::list<int>>(l, std::next(l.begin())));

    EXPECT_EQ(l.size(), sz_ori + v.size());
    EXPECT_EQ(*l.begin(), -1);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}