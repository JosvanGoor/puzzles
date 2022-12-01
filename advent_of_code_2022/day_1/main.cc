#include <algorithm>
#include <charconv>
#include <fmt/format.h>
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::int64_t> elves;
    elves.push_back(0);

    std::int64_t calories{};
    std::string buffer;

    while (!std::cin.eof())
    {
        std::getline(std::cin, buffer);
        
        if (buffer.empty())
        {
            elves.push_back(0);
            continue;
        }
        
        std::from_chars(buffer.data(), buffer.data() + buffer.size(), calories);
        elves.back() += calories;
    }

    std::int64_t max = *std::max_element(elves.begin(), elves.end());
    fmt::print("Elf with most calories has {}\n", max);

    std::int64_t top3{};
    for (std::size_t idx = 0; idx < 3; ++idx)
    {
        auto it = std::max_element(elves.begin(), elves.end());
        top3 += *it;
        *it = 0;
    }

    fmt::print("Top3 elves with most calories have a combined: {}\n", top3);
}
