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

int closest(Point location, vector<Point> const &points)
{
    int index = -1;
    size_t mindist = std::numeric_limits<size_t>::max();

    for (size_t idx = 0; idx != points.size(); ++idx)
    {
        size_t distance = manhattan_distance(location, points[idx]);

        if (distance == mindist)
            index = -1;
        else if (distance < mindist)
        {
            mindist = distance;
            index = idx;
        }
    }

    return index;
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

    cout << "grid size: " << width << " x " << height << "\n";
    vector<int> counts(points.size(), 0);

    for (size_t idx = 0; idx != width; ++idx)
    {
        for (size_t idy = 0; idy != height; ++idy)
        {
            int index = closest(Point{idx, idy}, points);
            if (index == -1) continue;
            ++counts[index];
        }
    }

    // if a class hits the edge its infinite.
    // we check highest and lowers rows first.
    for (size_t idx = 0; idx != width; ++idx)
    {
        int index = closest(Point{idx, 0}, points);
        int index2 = closest(Point{idx, height - 1}, points);
        
        if (index != -1)
            counts[index] = -1;
        
        if (index2 != -1)
            counts[index2] = -1;
    }

    //side rows
    for (size_t idx = 0; idx != height; ++idx)
    {
        int index = closest(Point{0, idx}, points);
        int index2 = closest(Point{width - 1, idx}, points);
        
        if (index != -1)
            counts[index] = -1;
        
        if (index2 != -1)
            counts[index2] = -1;
    }

    size_t maxclass = 0;
    int space = counts[0];
    for (size_t idx = 1; idx != counts.size(); ++idx)
    {
        if (counts[idx] > space)
        {
            space = counts[idx];
            maxclass = idx;
        }
    }

    cout << "biggest class is " << maxclass << " with a size of " << space << "\n";
}