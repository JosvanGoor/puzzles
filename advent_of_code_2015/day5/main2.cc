#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool has_repeating_pair(string const &text)
{
    for (size_t idx = 0; idx < text.size() - 2; ++idx)
    {
        if (text.find(text.substr(idx, 2), idx + 2) != string::npos)
        {
            cout << "'" << text << "' has repeating pair: '";
            cout << text.substr(idx, 2) << "'\n";
            return true;
        }
    }

    // cout << "'" << text << "' has no repeating pair\n";
    return false;
}

bool repeats_plus_one(string const &text)
{
    for (size_t idx = 0; idx < text.size() - 2; ++idx)
    {
        if (text[idx] == text[idx + 2])
            return true;
    }

    return false;
}

int main()
{
    string buffer;
    size_t count = 0;

    while (getline(cin, buffer))
    {
        if (has_repeating_pair(buffer)
            && repeats_plus_one(buffer))
        {
            ++count;
        }
    }

    cout << "Nice strings: " << count << "\n";

}