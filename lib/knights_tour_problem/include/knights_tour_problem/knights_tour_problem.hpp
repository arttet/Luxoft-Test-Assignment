#pragma once

#include <vector>

#include <knights_tour_problem/export.h>

using board_t = std::vector<std::vector<int>>;

KNIGHTS_TOUR_PROBLEM_EXPORT board_t solve_knights_tour_problem(int n, int x, int y);
