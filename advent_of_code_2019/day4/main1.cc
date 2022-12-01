#include <iostream>
#include <string>

using namespace std;

bool meets_criteria(size_t passwd)
{
    string number = to_string(passwd);

    bool adjacent = false;

    char min = '0';
    char prev = '1';
    for (char ch : number)
    {
        adjacent = adjacent | (prev == ch);
        
        if (ch < min)
            return false;
        
        min = ch;
        prev = ch;
    }

    return adjacent;
}

int main()
{
    const size_t LOWER = 178416;
    const size_t UPPER = 676461;

    size_t valid = 0;
    for (size_t idx = LOWER; idx <= UPPER; ++idx)
    {
        if (meets_criteria(idx))
            ++valid;
    }

    cout << "valid: " << valid << "\n";
}