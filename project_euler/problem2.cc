#include <cstdint>
#include <fmt/format.h>

std::int64_t fibonacci()
{
    static std::int64_t first = 1;
    static std::int64_t second = 2;

    std::int64_t result = first + second;
    std::swap(first, second);
    second = result;

    return result;
}

int main()
{
    std::int64_t result = 2;

    while (true)
    {
        std::int64_t value = fibonacci();
        if (value >= 4'000'000)
            break;
        
        if (value % 2 == 0)
            result += value;
    }

    fmt::print("Result: {}\n", result);
}