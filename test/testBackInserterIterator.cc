#include "iterator.h"
#include <gtest/gtest.h>
#include <deque>

TEST(TEST_ITERATOR, TEST_BACK_INSTERT)
{
    std::deque<int> de;
    xtl::back_inserter_iterator<std::deque<int>> back_iter(de);
    for (auto i = 0; i < 10; ++i)
    {
        back_iter = i;
    }

    EXPECT_EQ(de.size(), 10);
    EXPECT_EQ(de.front(), 0);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}