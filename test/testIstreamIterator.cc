#include "iterator.h"
#include <gtest/gtest.h>

#include <istream>
#include <algorithm>

TEST(TEST_ITERATOR, TEST_ISTREAM)
{
    std::istringstream str("1 3 5 7 8 9 10");

    auto iter = std::find_if(xtl::istream_iterator<int>(str), xtl::istream_iterator<int>(), [](int i) {
        return i % 2 == 0;
    });

    EXPECT_EQ(*iter, 8);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}