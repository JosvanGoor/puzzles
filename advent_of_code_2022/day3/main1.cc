#include <fmt/format.h>
#include <iostream>
#include <set>

int main()
{
    int result = 0;

    while (true)
    {
        std::string packing;
        std::getline(std::cin, packing);
        
        char double_packed{};
        std::set<char> c1{packing.begin(), packing.begin() + packing.size() / 2};
        std::set<char> c2{packing.begin() + packing.size() / 2, packing.end()};
        std::set_intersection(c1.begin(), c1.end(), c2.begin(), c2.end(), &double_packed);
        
        result += std::islower(double_packed) ? (double_packed - 'a' + 1) : (double_packed - 'A' + 27);

        if (std::cin.eof())
            break;
    }

    fmt::print("Result: {}\n", result);
}
