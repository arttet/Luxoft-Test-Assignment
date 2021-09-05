#include <increment_number_problem/increment_number_problem.hpp>

#include <gtest/gtest.h>

using TestPairSuite = ::testing::TestWithParam<std::tuple<int, int>>;

TEST_P(TestPairSuite, TestIncrementInteger)
{
    auto const [num, n] = GetParam();
    EXPECT_EQ(num, increase_number(num, n));
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(TestCombine, TestPairSuite, ::testing::Combine(
    ::testing::Values(8, 16, 32, 64, 128, 256, 512, 1024, 2048),
    ::testing::Values(2, 4, 6, 8, 10)
));
// clang-format on

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
