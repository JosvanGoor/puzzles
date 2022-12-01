#include <iostream>
#include <set>
#include <string>

using namespace std;

class Point
{
    public:
        int x;
        int y;
};


bool operator<(Point const &lhs, Point const &rhs)
{
    if (lhs.x == rhs.x)
        return lhs.y < rhs.y;
    return lhs.x < rhs.x;
}

int main()
{
    set<Point> delivered;
    Point position{0, 0};
    delivered.insert(position);

    while (!cin.eof())
    {
        switch (cin.get())
        {
            case '>': 
                ++position.x;
            break;

            case '<':
                --position.x;
            break;

            case '^':
                --position.y;
            break;

            case 'v':
                ++position.y;
            break;
        }

        delivered.insert(position);
    }

    cout << "Delivered count: " << delivered.size() << "\n";
}