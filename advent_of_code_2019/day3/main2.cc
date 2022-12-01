#include "main.ih"
#include <limits>

struct Location
{
    int wire_one_dist = -1;
    int wire_two_dist = -1;

    int time()
    {
        if (wire_one_dist == -1 || wire_two_dist == -1)
            return numeric_limits<int>::max();
        return wire_one_dist + wire_two_dist;
    }
};

int main(int argc, char *argv[])
{
    vector<Instr> wire_one = parse_line();
    vector<Instr> wire_two = parse_line();

    auto [min1, max1] = dimensions(wire_one);
    auto [min2, max2] = dimensions(wire_two);

    Point min = {std::min(min1.x, min2.x), std::min(min1.y, min2.y)};
    Point max = {std::max(max1.x, max2.x), std::max(max1.y, max2.y)};

    int width = max.x + abs(min.x) + 2;
    int height = max.y + abs(min.y) + 2;
    Point startp = {abs(min.x) + 1, abs(min.y) + 1};

    vector<int> overlaps;

    vector<Location> grid;
    grid.resize(width * height);
    size_t location = index(startp, width);
    size_t stored_start = location;
    grid[location] = {0, 0};

    int distance = 0;
    for (Instr const &instr : wire_one)
    {
        switch (instr.dir)
        {
            case 'R':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location += 1;
                    grid[location].wire_one_dist = grid[location].wire_one_dist == -1 ? distance : grid[location].wire_one_dist;
                }
            break;

            case 'L':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location -= 1;
                    grid[location].wire_one_dist = grid[location].wire_one_dist == -1 ? distance : grid[location].wire_one_dist;
                }
            break;

            case 'U':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location -= width;
                    grid[location].wire_one_dist = grid[location].wire_one_dist == -1 ? distance : grid[location].wire_one_dist;
                }
            break;

            case 'D':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location += width;
                    grid[location].wire_one_dist = grid[location].wire_one_dist == -1 ? distance : grid[location].wire_one_dist;
                }
            break;
        }
    }

    // some delish copy-paste
    location = stored_start;
    distance = 0;
    for (Instr const &instr : wire_two)
    {
        switch (instr.dir)
        {
            case 'R':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location += 1;
                    grid[location].wire_two_dist = grid[location].wire_two_dist == -1 ? distance : grid[location].wire_two_dist;
                    if (grid[location].wire_one_dist != -1)
                        overlaps.push_back(location);
                }
            break;

            case 'L':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location -= 1;
                    grid[location].wire_two_dist = grid[location].wire_two_dist == -1 ? distance : grid[location].wire_two_dist;
                    if (grid[location].wire_one_dist != -1)
                        overlaps.push_back(location);
                }
            break;

            case 'U':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location -= width;
                    grid[location].wire_two_dist = grid[location].wire_two_dist == -1 ? distance : grid[location].wire_two_dist;
                    if (grid[location].wire_one_dist != -1)
                        overlaps.push_back(location);
                }
            break;

            case 'D':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    ++distance;
                    location += width;
                    grid[location].wire_two_dist = grid[location].wire_two_dist == -1 ? distance : grid[location].wire_two_dist;
                    if (grid[location].wire_one_dist != -1)
                        overlaps.push_back(location);
                }
            break;
        }
    }

    int mintime = numeric_limits<int>::max();
    for (int overlap : overlaps)
    {
        cout << "time: " << grid[overlap].time() << "\n";
        mintime = std::min(grid[overlap].time(), mintime);
    }

    cout << "mintime: " << mintime << "\n";
}