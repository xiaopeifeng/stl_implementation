#include "iterator.h"
#include <gtest/gtest.h>
#include <vector>
#include <deque>
#include <algorithm>

using std::deque;
using std::vector;

TEST(TEST_ITERATOR, TEST_FRONT_ITERATOR)
{
    vector<int> v{1, 2, 3, 4, 5};
    deque<int> de;

    std::copy(v.begin(), v.end(), xtl::front_inserter_iterator<deque<int>>(de));

    EXPECT_EQ(de.size(), v.size());
    EXPECT_EQ(de.front(), 5);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}