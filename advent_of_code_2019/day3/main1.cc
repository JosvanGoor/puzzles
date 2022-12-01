#include "main.ih"
#include <limits>

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

    vector<Point> overlaps;

    vector<char> grid;
    grid.resize(width * height, '.');
    size_t location = index(startp, width);
    size_t stored_start = location;
    grid[location] = 'O';

    for (Instr const &instr : wire_one)
    {
        switch (instr.dir)
        {
            case 'R':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location += 1;
                    grid[location] = '1';
                }
            break;

            case 'L':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location -= 1;
                    grid[location] = '1';
                }
            break;

            case 'U':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location -= width;
                    grid[location] = '1';
                }
            break;

            case 'D':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location += width;
                    grid[location] = '1';
                }
            break;
        }
    }

    // some delish copy-paste
    location = stored_start;
    for (Instr const &instr : wire_two)
    {
        switch (instr.dir)
        {
            case 'R':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location += 1;
                    if (grid[location] == '1')
                    {
                        grid[location] = 'X';
                        overlaps.push_back(index_to_point(location, width));
                    }
                    else
                        grid[location] = '2';
                }
            break;

            case 'L':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location -= 1;
                    if (grid[location] == '1')
                    {
                        grid[location] = 'X';
                        overlaps.push_back(index_to_point(location, width));
                    }
                    else
                        grid[location] = '2';
                }
            break;

            case 'U':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location -= width;
                    if (grid[location] == '1')
                    {
                        grid[location] = 'X';
                        overlaps.push_back(index_to_point(location, width));
                    }
                    else
                        grid[location] = '2';
                }
            break;

            case 'D':
                for (int idx = 0; idx < instr.steps; ++idx)
                {
                    location += width;
                    if (grid[location] == '1')
                    {
                        grid[location] = 'X';
                        overlaps.push_back(index_to_point(location, width));
                    }
                    else
                        grid[location] = '2';
                }
            break;
        }
    }

    // print_grid(grid, width);

    auto manhattan = [](Point p1, Point p2) -> int
    {
        return abs(p1.x - p2.x) + abs(p1.y - p2.y);
    };

    int mindist = numeric_limits<int>::max();
    for (Point overlap : overlaps)
    {
        mindist = std::min(mindist, manhattan(startp, overlap));
    }

    cout << "mindist: " << mindist << "\n";
}