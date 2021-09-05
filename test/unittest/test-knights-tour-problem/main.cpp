#include <knights_tour_problem/knights_tour_problem.hpp>

#include <gtest/gtest.h>

using TestTupleSuite = ::testing::TestWithParam<std::tuple<int, int, int, std::vector<std::vector<int>>>>;

TEST_P(TestTupleSuite, TestKnightsTourProblem)
{
    auto const [x, y, n, expected_result] = GetParam();
    EXPECT_EQ(expected_result, solve_knights_tour_problem(n, x, y));
}

// clang-format off
INSTANTIATE_TEST_SUITE_P(TestEightBoard, TestTupleSuite, ::testing::ValuesIn({
    std::tuple{
        0,
        0,
        8,
        board_t{
            {0, 59, 38, 33, 30, 17, 8, 63},
            {37, 34, 31, 60, 9, 62, 29, 16},
            {58, 1, 36, 39, 32, 27, 18, 7},
            {35, 48, 41, 26, 61, 10, 15, 28},
            {42, 57, 2, 49, 40, 23, 6, 19},
            {47, 50, 45, 54, 25, 20, 11, 14},
            {56, 43, 52, 3, 22, 13, 24, 5},
            {51, 46, 55, 44, 53, 4, 21, 12},
        }
    },
    // std::tuple{
    //     7,
    //     7,
    //     8,
    //     board_t{
    //         {46, 33, 20, 29, 4, 13, 18, 63},
    //         {35, 30, 47, 32, 19, 62, 3, 12},
    //         {48, 45, 34, 21, 28, 5, 14, 17},
    //         {59, 36, 31, 50, 61, 16, 11, 2},
    //         {44, 49, 60, 37, 22, 27, 6, 15},
    //         {55, 58, 41, 24, 51, 8, 1, 10},
    //         {40, 43, 56, 53, 38, 23, 26, 7},
    //         {57, 54, 39, 42, 25, 52, 9, 0},
    //     }
    // },
}));

INSTANTIATE_TEST_SUITE_P(TestFourBoard, TestTupleSuite, ::testing::ValuesIn({
    std::tuple{
        0,
        0,
        2,
        std::vector<std::vector<int>>{
            {0, -1},
            {-1, -1},
        }
    },
}));

INSTANTIATE_TEST_SUITE_P(TestOneBoard, TestTupleSuite, ::testing::ValuesIn({
    std::tuple{
        0,
        0,
        1,
        board_t{
            {0},
        }
    },
}));

INSTANTIATE_TEST_SUITE_P(TestInvalidArgument, TestTupleSuite, ::testing::ValuesIn({
    std::tuple{
        1,
        1,
        0,
        board_t{}
    },
}));
// clang-format on

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
