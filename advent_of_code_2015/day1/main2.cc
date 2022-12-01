#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    string buffer;

    while(getline(cin, buffer))
    {
        int floor = 0;
        
        for (size_t idx = 0; idx != buffer.size(); ++idx)
        {
            floor += buffer[idx] == '(' ? 1 : -1;
            if (floor == -1)
            {
                cout << "Entered basement in step " << idx + 1 << "\n";
                return 0;
            }
        }

        
    }
}