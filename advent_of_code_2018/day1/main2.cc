#include <iostream>
#include <set>
#include <string>
#include <vector>

using namespace std;

int read()
{
    string line;
    getline(cin, line);

    bool plus = line[0] == '+';
    int val = stoi(line.substr(1));

    return plus ? val : -val;
}

int main()
{
    vector<int> sequence;
    while (!cin.eof())
        sequence.push_back(read());

    // cout << "Buffered " << sequence.size() << " frequencies\n";
    
    int total = 0;
    set<int> used;
    used.insert(0);

    while (true)
    {
        for (int i : sequence)
        {
            total += i;

            if (used.find(total) != used.end())
            {
                cout << "Found first repeating frequency: " << total << "\n";
                return 0;
            }

            used.insert(total);
        }
    }
}