#include <iostream>
#include <string>

using namespace std;

bool meets_criteria(size_t passwd)
{
    string number = to_string(passwd);

    bool adjacent = false;
    int groupsize = 0;

    char min = '0';
    char prev = '1';
    for (char ch : number)
    {
        adjacent = adjacent | (prev == ch);
        
        if (prev == ch)
            ++groupsize;
        else
        {
            if (groupsize > 1 && groupsize % 2 != 0)
            {
                cout << "groupsize bounced: " << passwd << "\n";
                return false; //uneven group
            }
            
            prev = ch;
            groupsize = 1;
        }

        if (ch < min)
            return false;
        
        min = ch;
    }

    if (groupsize == 1)
        return adjacent;
    else if (groupsize % 2 != 0)
    {
        cout << "groupsize bounced (end): " << passwd << "\n";
        return false;
    }
    return true;
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