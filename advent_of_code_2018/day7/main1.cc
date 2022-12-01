#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Constraint
{
    bool placed = false;
    vector<char> requires;
    vector<char> required_by;
};

bool satisfied(Constraint const &constraint, string const &plan)
{
    for (char c : constraint.requires)
    {
        if (plan.find(c) == string::npos)
            return false;
    }
    return true;
}

int main()
{
    array<Constraint, 26> constraints {};

    while (!cin.eof())
    {
        char step;
        char requires;

        cin.ignore(5); // 'Step '
        cin >> requires;
        cin.ignore(30); // ' must be finished before step '
        cin >> step;
        cin.ignore(12); //' can begin.\n'

        cout << step << " requires " << requires << "\n";
        constraints[step - 'A'].requires.push_back(requires);
        constraints[requires - 'A'].required_by.push_back(step);
    }

    string plan;
    while(plan.size() != 26)
    {
        for (size_t idx = 0; idx < 26; ++idx)
        {
            if (!constraints[idx].placed && satisfied(constraints[idx], plan))
            {
                plan += static_cast<char>('A' + idx);
                constraints[idx].placed = true;
                break;
            }
        }

        cout << plan.size() << " / '" << plan << "'\n";
    }

    cout << plan.size() << " / '" << plan << "'\n";
}