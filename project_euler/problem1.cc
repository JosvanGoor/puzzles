#include <cstdint>
#include <fmt/format.h>

int main()
{
    std::int64_t result = 0;

    for (std::int64_t value = 3; value < 1000; value += 3)
        result += value;

    for (std::int64_t value = 5; value < 1000; value += 5)
        result += value % 3 == 0 ? 0 : value;

    fmt::print("Result: {}\n", result);
}