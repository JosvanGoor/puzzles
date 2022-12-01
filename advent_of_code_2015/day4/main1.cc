#include <iostream>
#include <string>

#include "md5.hpp"

using namespace std;

int main()
{

    string prefix = "bgvyzdsv";

    for (size_t idx = 0; ; ++idx)
    {
        string test = prefix + to_string(idx);

        string hash = md5(test);
        if (hash.find_first_not_of('0') == 6) //5 for solution 1
        {
            cout << test << "\n";
            return 0;
        }
    }
}