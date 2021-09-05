#include <knights_tour_problem/knights_tour_problem.hpp>

#include <boost/range/combine.hpp>

#include <atomic>
#include <functional>
#include <future>

namespace {

int constexpr g_init = -1;
int constexpr g_directions[][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

int valid(int n, int x, int y)
{
    return x >= 0 && x < n && y >= 0 && y < n;
}

int valid(board_t const & board, int n, int x, int y)
{
    return valid(n, x, y) && board[x][y] == g_init;
}

bool solve_kt_problem(board_t & board, int n, int x, int y, int move, std::atomic_bool & stop_thread)
{
    if (move == n * n) {
        stop_thread = true;
        return true;
    }

    if (stop_thread) {
        return false;
    }

    for (auto const [dx, dy] : g_directions) {
        int const next_x = x + dx;
        int const next_y = y + dy;
        if (valid(board, n, next_x, next_y)) {
            board[next_x][next_y] = move;
            if (solve_kt_problem(board, n, next_x, next_y, move + 1, stop_thread)) {
                return true;
            }

            board[next_x][next_y] = -1;
        }
    }

    return false;
}

} // namespace

board_t solve_knights_tour_problem(int n, int x, int y)
{
    if (!valid(n, x, y)) {
        return {};
    }

    std::atomic_bool stop_thread = false;
    board_t init_board(n, std::vector<int>(n, g_init));
    int move = ++init_board[x][y];

    if (n >= 5) {
        size_t constexpr num = std::size(g_directions);
        std::vector<board_t> boards(num, init_board);
        std::vector<std::future<bool>> results(num);

        for (auto const & [direction, board, result] : boost::combine(g_directions, boards, results)) {
            auto const [dx, dy] = direction;
            int const next_x = x + dx;
            int const next_y = y + dy;
            if (valid(n, next_x, next_y)) {
                int const next_move = move + 1;
                board[next_x][next_y] = next_move;

                // clang-format off
                result = std::async(std::launch::async,
                    solve_kt_problem, std::ref(board), n, next_x, next_y, next_move + 1, std::ref(stop_thread));
                // clang-format on
            }
        }

        board_t * result = nullptr;
        for (auto const & [board, rc] : boost::combine(boards, results)) {
            if (rc.valid()) {
                if (auto const ok = rc.get(); ok && !result) {
                    result = &board;
                }
            }
        }

        if (result) {
            return *result;
        }
    }

    return init_board;
}
