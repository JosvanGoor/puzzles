#include <fmt/format.h>
#include <iostream>
#include <set>

template <typename T>
struct push_back_set : public std::set<T>
{
    void push_back(const T& t)
    {
        this->insert(t);
    }
};

std::set<char> read_backpack()
{
    std::string packing;
    std::getline(std::cin, packing);
    return {packing.begin(), packing.end()};
}

int main()
{
    int result = 0;

    while (true)
    {
        char badge{};
        push_back_set<char> b12;
        
        auto b1 = read_backpack();
        auto b2 = read_backpack();
        auto b3 = read_backpack();
        
        std::set_intersection(b1.begin(), b1.end(), b2.begin(), b2.end(), std::back_inserter(b12));
        std::set_intersection(b12.begin(), b12.end(), b3.begin(), b3.end(), &badge);

        result += std::islower(badge) ? (badge - 'a' + 1) : (badge - 'A' + 27);

        if (std::cin.eof())
            break;
    }

    fmt::print("Result: {}\n", result);
}
