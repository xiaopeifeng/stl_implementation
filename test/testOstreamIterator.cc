#include "iterator.h"
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <algorithm>

TEST(TEST_ITERATOR, TEST_OSTREAM)
{
    std::stringstream ss;
    xtl::ostream_iterator<int> i1(ss, ", ");
    std::fill_n(i1, 5, -1);
    EXPECT_STREQ(ss.str().c_str(), "-1, -1, -1, -1, -1, ");
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}