#include <iostream>
#include <fmt/format.h>

struct Range
{
    int start{};
    int end{};
};

Range read()
{
    Range range;
    std::cin >> range.start;
    std::cin.ignore(1);
    std::cin >> range.end;
    return range;
}

int main()
{
    int full_overlaps = 0;
    int partial_overlaps = 0;

    while (true)
    {
        Range r1 = read();
        std::cin.ignore(1);
        Range r2 = read();

        if ((r1.start <= r2.start && r1.end >= r2.end) || (r1.start >= r2.start && r1.end <= r2.end))
            ++full_overlaps;
        
        if ((r1.start <= r2.start && r1.end >= r2.start) || (r1.start <= r2.end && r1.end >= r2.start))
            ++partial_overlaps;

        if (std::cin.eof())
            break;
    }

    fmt::print("   Full Overlaps: {}\n", full_overlaps);
    fmt::print("Partial Overlaps: {}\n", partial_overlaps);
}