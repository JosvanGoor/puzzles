#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

bool has_forbidden(string const &str)
{
    if (str.find("ab") != string::npos) return true;
    if (str.find("cd") != string::npos) return true;
    if (str.find("pq") != string::npos) return true;
    if (str.find("xy") != string::npos) return true;
    return false;
}

bool has_repeating(string const &str)
{
    for (size_t idx = 0; idx != str.size() - 1; ++idx)
    {
        if (str[idx] == str[idx + 1])
            return true;
    }

    return false;
}

bool vowels_ok(string const &str)
{
    size_t vowels = 0;

    vowels += count(str.begin(), str.end(), 'a');
    vowels += count(str.begin(), str.end(), 'e');
    vowels += count(str.begin(), str.end(), 'i');
    vowels += count(str.begin(), str.end(), 'o');
    vowels += count(str.begin(), str.end(), 'u');
    
    return vowels >= 3;
}

int main()
{

    string buffer;
    size_t count = 0;

    while(getline(cin, buffer))
    {
        cout << "'" << buffer << "'\n";

        if (vowels_ok(buffer)
            && has_repeating(buffer)
            && !has_forbidden(buffer))
        {
            ++count;
        }
    }

    cout << "Nice strings: " << count << "\n";
}