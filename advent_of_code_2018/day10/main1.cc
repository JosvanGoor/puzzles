#include "main.ih"

struct Star
{
    Position pos;
    Velocity vel;

    void update()
    {
        pos = pos + vel;
    }
};

Star read_star()
{
    Star rval;
    cin >> rval.pos;
    cin >> rval.vel;
    return rval;
}

size_t grid_size(vector<Star> const &stars)
{
    int minx = numeric_limits<int>::max();
    int maxx = numeric_limits<int>::min();
    int miny = minx;
    int maxy = maxx;

    for (Star const &star : stars)
    {
        minx = min(minx, star.pos.xpos);
        maxx = max(maxx, star.pos.xpos);
        miny = min(miny, star.pos.ypos);
        maxy = max(maxy, star.pos.ypos);
    }

    size_t width = maxx - minx + 1;
    size_t height = maxy - miny + 1;
    return width * height;
}

void write_to_console(vector<Star> const &stars)
{
    int minx = numeric_limits<int>::max();
    int maxx = numeric_limits<int>::min();
    int miny = minx;
    int maxy = maxx;

    for (Star const &star : stars)
    {
        minx = min(minx, star.pos.xpos);
        maxx = max(maxx, star.pos.xpos);
        miny = min(miny, star.pos.ypos);
        maxy = max(maxy, star.pos.ypos);
    }

    int xpos = minx;
    int ypos = miny;
    int width = maxx - minx + 1;
    int height = maxy - miny + 1;
    vector<vector<bool>> grid;
    grid.resize(width, vector<bool>(height));

    for (Star const &star : stars)
        grid[star.pos.xpos - xpos][star.pos.ypos - ypos] = true;

    for (int idy = 0; idy < height; ++idy)
    {
        for (int idx = 0; idx < width; ++idx)
            cout << (grid[idx][idy] ? '#' : ' ');
        cout << "\n";
    }
}

int main()
{
    vector<Star> stars;

    while (!cin.eof())
        stars.push_back(read_star());

    size_t size = grid_size(stars);
    for (size_t time = 0; true; ++time)
    {
        vector<Star> next_position(stars);
        for (Star &star : next_position)
            star.update();

        size_t next_size = grid_size(next_position);

        if (next_size > size)
        {
            write_to_console(stars);
            cout << "That took " << time << " seconds!\n"; // part 2
            return 0;
        }

        stars.swap(next_position);
        size = next_size;
    }
}