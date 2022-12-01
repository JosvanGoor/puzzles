#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

unordered_map<string, char> read_rules()
{
    unordered_map<string, char> rules;

    while(!cin.eof())
    {
        char result;
        string rule;

        cin >> rule;
        cin.ignore(4); //ignore ' => '
        cin >> result;
        cin.ignore(1); //ignore '\n'

        rules[rule] = result;
    }

    return rules;
}

vector<char> initial_state()
{
    cin.ignore(15); // ignore 'initial state: '
    string buf;
    getline(cin, buf);

    return vector<char>(buf.begin(), buf.end());
}

string environment(vector<char> const &plants, size_t idx)
{
    string sig;
    
    switch(idx)
    {
        case 0:
            sig += "..";
            sig += string(plants.begin(), plants.begin() + 3);
            return sig;
        
        case 1:

            sig += ".";
            sig += string(plants.begin(), plants.begin() + 4);
            return sig;

        default:
        break;
    }

    if (idx == (plants.size() - 2))
    {
        auto it = plants.begin() + idx;
        return string(it - 2, it + 2) + '.';
    }
    else if (idx == (plants.size() - 1))
    {
        auto it = plants.begin() + idx;
        return string(it - 2, it + 1) + "..";
    }

    auto it = plants.begin() + idx;
    return string(it - 2, it + 3);
}

int main()
{
    int first = 0;
    vector<char> plants = initial_state();
    unordered_map<string, char> rules = read_rules();

    string original = string(plants.begin(), plants.end());
    cout << original << "\n";

    for (size_t iterations = 20; iterations--; )
    {
        if (find(plants.begin(), plants.begin() + 3, '#')
             != plants.begin() + 3)
        {
            first -= 2;
            plants.insert(plants.begin(), {'.', '.'});
        }

        if (find(plants.end() - 3, plants.end(), '#')
            != plants.end())
        {
            plants.insert(plants.end(), {'.', '.'});
        }
        vector<char> nextgen(plants.size(), '.');

        // cout << "\n\n  # now   env    new\n";
        for (size_t idx = 0; idx != plants.size(); ++idx)
        {
            // cout << setw(3) << first + static_cast<int>(idx) << " ";
            // cout << "[" << plants[idx] << "]: ";
            string env = environment(plants, idx);
            // cout << env << " => ";

            char result = '?';
            if (auto it = rules.find(env); it != rules.end())
                result = it->second;
            // cout << result << "\n";
            nextgen[idx] = result;
        }
        plants.swap(nextgen);
    }

    // cout << string(-first, ' ') << original << "\n";
    // cout << string(plants.begin(), plants.end()) << "\n";

    int score = 0;
    for (size_t idx = 0; idx < plants.size(); ++idx)
    {
        score += (plants[idx] == '#' ? idx + first : 0);
    }
    cout << "score: " << score << "\n";
    
}