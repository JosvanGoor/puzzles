#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t collapse_polymer(vector<char> polymer)
{
    int react_diff = abs('a' - 'A');
    size_t oldsize = 0;
    while(oldsize != polymer.size())
    {
        oldsize = polymer.size();

        for (size_t idx = 0; idx < polymer.size() - 1; ++idx)
        {
            if (abs(polymer[idx] - polymer[idx + 1]) == react_diff)
            {
                polymer.erase(polymer.begin() + idx, polymer.begin() + idx + 2);
                --idx;
            }
        }
    }

    return polymer.size();
}

int main()
{
    
    vector<char> polymer {
        istreambuf_iterator<char>(cin),
        istreambuf_iterator<char>()
    };
    cout << "Read polymer of size: " << polymer.size() << "\n";

    size_t minsize = polymer.size();
    for (size_t idx = 0; idx < 26; ++idx)
    {
        char current = 'a' + idx;
        vector<char> filtered{polymer};

        auto it = remove_if(filtered.begin(), filtered.end(), [=](char c)
        {
            if (c == current || c == toupper(current))
                return true;
            return false;
        });
        filtered.erase(it, filtered.end());

        minsize = min(collapse_polymer(filtered), minsize);
    }

    cout << "Smallest collapsed polymer size: " << minsize << "\n";
}