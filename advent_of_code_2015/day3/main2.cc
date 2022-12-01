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
    bool robo = false;
    set<Point> delivered;
    Point position{0, 0};
    Point robo_position{0, 0};
    delivered.insert(position);

    while (!cin.eof())
    {
        switch (cin.get())
        {
            case '>': 
                ++(robo ? robo_position : position).x;
            break;

            case '<':
                --(robo ? robo_position : position).x;
            break;

            case '^':
                --(robo ? robo_position : position).y;
            break;

            case 'v':
                ++(robo ? robo_position : position).y;
            break;
        }

        robo = !robo;
        delivered.insert(robo ? robo_position : position);
    }

    cout << "Delivered count: " << delivered.size() << "\n";
}