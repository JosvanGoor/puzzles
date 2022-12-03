#include <fmt/format.h>

#include <array>
#include <fstream>

void run_game(const std::array<std::array<int, 3>, 3>& scoring)
{
    int score = 0;
    std::fstream in{"input.txt"};

    char elf{};
    char you{};

    while (true)
    {
        in >> elf >> you;

        if (in.eof())
            break;

        score += scoring[elf - 'A'][you - 'X'];
    }

    fmt::print("Result: {}\n", score);
}

int main()
{
    std::array<std::array<int, 3>, 3> scoring_part1
    {{   
        //X     Y     Z
        {{4,    8,    3}},    // A (rock)
        {{1,    5,    9}},    // B (paper)
        {{7,    2,    6}}     // C (scissors)
    }};

    std::array<std::array<int, 3>, 3> scoring_part2
    {{   
        //X     Y     Z
        {{3,    4,    8}},    // A (rock)
        {{1,    5,    9}},    // B (paper)
        {{2,    6,    7}}     // C (scissors)
    }};

    run_game(scoring_part1);
    run_game(scoring_part2);
}