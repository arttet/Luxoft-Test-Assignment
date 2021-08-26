#include <increment_number_problem/increment_number_problem.hpp>

#include <fmt/format.h>
#include <gsl/span>

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(push)
#pragma warning(disable : 4459)
#endif

#include <boost/spirit/include/qi.hpp>

#if _MSC_VER && !__INTEL_COMPILER
#pragma warning(pop)
#endif

#include <cstdlib>
#include <string_view>

int main(int argc, char const * const * const argv)
{
    size_t num = 1024;
    size_t n = 8;

    auto const args = gsl::span(argv, size_t(argc));
    if (args.size() >= 2) {
        std::string_view const arg(args[1]);
        if (!boost::spirit::qi::parse(arg.begin(), arg.end(), num)) {
            fmt::print(stderr, "The argument {} should be unsigned integer\n", arg);
            return EXIT_FAILURE;
        }
    }

    if (args.size() >= 3) {
        std::string_view const arg(args[2]);
        if (!boost::spirit::qi::parse(arg.begin(), arg.end(), n) || n & 1U) {
            fmt::print(stderr, "The argument {} should be unsigned integer and even\n", arg);
            return EXIT_FAILURE;
        }
    }

    fmt::print(u8"Result: {}", increase_number(num, n));
    return EXIT_SUCCESS;
}
