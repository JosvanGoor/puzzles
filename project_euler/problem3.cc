#include <cstdint>
#include <fmt/format.h>

#include "sieve.h"

int main()
{   
    std::uint64_t input = 600'851'475'143;
    auto sieve = std::make_unique<Sieve<1'000'000>>();
    
    for (auto value = static_cast<std::uint64_t>(std::sqrt(input)); value--; )
    {
        if (sieve->is_prime(value) && input % value == 0)
            fmt::print("Result: {}\n", value);
    }
}