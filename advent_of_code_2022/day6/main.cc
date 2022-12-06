#include <fmt/format.h>
#include <iostream>
#include <set>

int main()
{
    std::string transmission;
    std::getline(std::cin, transmission);

    for (std::size_t idx = 4; idx <= transmission.size(); ++idx)
    {
        // overkill but i'm lazy
        std::set<char> marker{transmission.begin() + (idx - 4), transmission.begin() + idx};
        if (marker.size() == 4)
        {
            fmt::print("Part 1 result: {}\n", idx);
            break;
        }
    }

    for (std::size_t idx = 14; idx <= transmission.size(); ++idx)
    {
        std::set<char> marker{transmission.begin() + (idx - 14), transmission.begin() + idx};
        if (marker.size() == 14)
        {
            fmt::print("Part 2 result: {}\n", idx);
            break;
        }
    }
}