#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int evaluate_square(vector<vector<int>> const &grid, size_t topx, size_t lefty, size_t size = 3)
{
    int sum = 0;

    for (size_t idx = 0; idx != size; ++idx)
    {
        for (size_t idy = 0; idy != size; ++idy)
            sum += grid[topx + idx][lefty + idy];
    }

    return sum;
}

int main()
{
    size_t grid_width;
    size_t grid_height;
    int grid_serial_number;
    
    cin >> grid_serial_number;
    cin >> grid_width;
    cin >> grid_height;

    vector<vector<int>> grid;
    grid.resize(grid_width, vector<int>(grid_height, 0));

    for (size_t idy = 0; idy < grid_height; ++idy)
    {
        for (size_t idx = 0; idx < grid_width; ++idx)
        {
            int rack_id = idx + 11;
            int powerlevel = rack_id * (idy + 1);
            
            powerlevel += grid_serial_number;
            powerlevel *= rack_id;
            
            string text = to_string(powerlevel);
            powerlevel = text.size() >= 3 ? (text[text.size() - 3] - '0') : 0;
            powerlevel -= 5;
            
            grid[idx][idy] = powerlevel;
            // cout << setw(4) << powerlevel;
        }
        // cout << "\n";
    }

    int top_value = numeric_limits<int>::min();
    size_t top_size;
    size_t top_x;
    size_t top_y;
    for (size_t size = 0; size != 300; ++size)
    {
        cout << "Size " << setw(3) << size << "/300\r" << flush;
        for (size_t idx = 1; idx != (grid_width - (size - 1)); ++idx)
        {
            for (size_t idy = 0; idy != (grid_width - (size - 1)); ++idy)
            {
                int value = evaluate_square(grid, idx, idy, size);
                if (value > top_value)
                {
                    top_value = value;
                    top_size = size;
                    top_x = idx + 1;
                    top_y = idy + 1;
                }
            }
        }
    }

    cout << "Top x,y,size is " << top_x << "," << top_y << "," << top_size
        << " with " << top_value << " power\n";

}