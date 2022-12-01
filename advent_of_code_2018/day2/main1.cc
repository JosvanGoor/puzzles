#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

int main()
{
    size_t dubbles = 0;
    size_t tripples = 0;

    string buffer;

    while(getline(cin, buffer))
    {
        bool twice = false;
        bool thrice = false;
        size_t letters[26] = { };

        for (char c : buffer)
        {
            ++letters[c - 'a'];
        }

        for (size_t idx = 0; idx < 26; ++idx)
        {
            if (letters[idx] == 2)
                twice = true;
            if (letters[idx] == 3)
                thrice = true;
        }

        if (twice)
            ++dubbles;
        if (thrice)
            ++tripples;
    }

    cout << "checsum: " << dubbles * tripples << "\n";
}