#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


struct Point
{
    size_t x;
    size_t y;

    Point() 
    : x(0), y(0)
    { }

    Point(size_t x, size_t y)
    : x(x), y(y)
    { }
};

istream &operator>>(istream& in, Point &point)
{
    cin >> point.x;
    cin.ignore(); // ignore ','
    cin >> point.y;

    return in;
}   

inline size_t manhattan_distance(Point const &p1, Point const &p2)
{
    return (p1.x > p2.x ? p1.x - p2.x : p2.x - p1.x)
        + (p1.y > p2.y ? p1.y - p2.y : p2.y - p1.y);
}

int main()
{
    size_t width = 0;
    size_t height = 0;
    vector<Point> points;

    while(!cin.eof())
    {
        Point point;
        cin >> point;

        points.push_back(point);
        width = max(width, point.x + 1);
        height = max(height, point.y + 1);
    }

    size_t region_size = 0;
    size_t distance_limit = 10000;
    for (size_t idx = 0; idx != width; ++idx)
    {
        for (size_t idy = 0; idy != height; ++idy)
        {
            size_t sum = 0;
            Point current {idx, idy};
            for_each(points.begin(), points.end(), [&](Point const &point)
            {
                sum += manhattan_distance(current, point);
            });

            if (sum < distance_limit)
                region_size++;
        }
    }

    cout << "region size: " << region_size << "\n";
}