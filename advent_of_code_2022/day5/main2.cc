#include <fmt/format.h>
#include <iostream>
#include <vector>

std::vector<std::vector<char>> read_initial_setup()
{
    std::string buffer;
    std::vector<std::vector<char>> stacks;

    while (true)
    {
        std::getline(std::cin, buffer);
        if (buffer[1] == '1')
            break;

        for (std::size_t idx = 0; (1 + (4 * idx)) < buffer.size(); ++idx)
        {
            std::size_t crate = 1 + (4 * idx);
            if (buffer[crate] != ' ')
            {
                if (stacks.size() <= idx)
                    stacks.resize(idx + 1);
                stacks[idx].push_back(buffer[crate]);
            }
        }
    }

    std::getline(std::cin, buffer); // read empty line

    // flip them around, faster indexing
    for (auto& stack : stacks)
        stack = std::vector<char>{stack.rbegin(), stack.rend()};
    
    return stacks;
};

struct Instruction
{
    std::ptrdiff_t move{};
    std::size_t from{};
    std::size_t to{};
};

Instruction read_instruction()
{
    Instruction instruction;
    std::string buffer;
    std::cin >> buffer; // read 'move'
    std::cin >> instruction.move;
    std::cin >> buffer; // 'from'
    std::cin >> instruction.from;
    std::cin >> buffer; // 'to'
    std::cin >> instruction.to;
    instruction.from -= 1;
    instruction.to -= 1;
    return instruction;
}

int main()
{
    auto stacks = read_initial_setup();

    while (true)
    {
        auto instruction = read_instruction();
        if (instruction.from == instruction.to)
            continue;

        auto begin = stacks[instruction.from].end() - instruction.move;
        stacks[instruction.to].insert(stacks[instruction.to].end(), begin, stacks[instruction.from].end());
        stacks[instruction.from].erase(begin, stacks[instruction.from].end());

        if (std::cin.eof())
            break;
    }

    fmt::print("Result: ");
    for (const auto& stack : stacks)
        fmt::print("{}", stack.back());
    fmt::print("\n");
}