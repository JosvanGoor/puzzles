#include <cstdint>
#include <fmt/format.h>

int main()
{
    for (std::int64_t value = 40; ; value += 20)
    {
        bool valid = true;
        for (std::size_t divisor = 2; divisor <= 20; ++divisor)
        {
            if (value % divisor != 0)
            {
                valid = false;
                break;
            }
        }

        if (valid)
        {
            fmt::print("Result: {}\n", value);
            return 0;
        }
    }
}