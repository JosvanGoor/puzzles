#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

size_t label_diff(string const &lhs, string const &rhs)
{
    size_t diff = 0;
    for (size_t idx = 0; idx != lhs.size(); ++idx)
        diff += lhs[idx] - rhs[idx] ? 1 : 0;
    return diff;
}

string equal_part(string const &lhs, string const &rhs)
{
    string rval;
    rval.reserve(lhs.size() - 1);

    for (size_t idx = 0; idx != lhs.size(); ++idx)
    {
        if (lhs[idx] == rhs[idx])
            rval.push_back(lhs[idx]);
    }
    
    return rval;
}

int main()
{
    size_t dubbles = 0;
    size_t tripples = 0;

    string buffer;
    vector<string> labels;

    while (getline(cin, buffer))
        labels.push_back(buffer);

    for (string const &lhs : labels)
    {
        for  (string const &rhs : labels)
        {
            size_t difference = label_diff(rhs, lhs);

            if (difference == 1)
            {
                cout << "Equal part: " << equal_part(lhs, rhs) << "\n";
                return 0;
            }
        }
    }
}

//jbbenqtlaxhivmwyscjukztdp correct