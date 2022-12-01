#include <cstdint>
#include <fmt/format.h>

int main()
{
    std::uint64_t max = 0;

    for (std::size_t a = 999; a > 99; a--)
    {
        for (std::size_t b = 999; b > 99; b--)
        {
            std::string number = std::to_string(a * b);
            if (std::equal(number.begin(), number.end(), number.rbegin()))
                max = std::max(max, a * b);
        }
    }

    fmt::print("Result: {}\n", max);
}
