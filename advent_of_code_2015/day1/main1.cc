#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string buffer;

    while(getline(cin, buffer))
    {
        int up = count(buffer.begin(), buffer.end(), '(');
        int down = count(buffer.begin(), buffer.end(), ')');

        cout << "Floor: " << up - down << "\n";
    }
}