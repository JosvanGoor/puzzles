#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

#include <chrono>
#include <thread>
#include <unistd.h>

using namespace std;

struct Constraint
{
    bool placed = false;
    vector<char> requires;
    vector<char> required_by;
};

struct Task
{
    char step = '\0';
    size_t time_left = 0;
};

bool satisfied(Constraint const &constraint, string const &plan)
{
    for (char c : constraint.requires)
    {
        if (plan.find(c) == string::npos)
        {
            cout << "Constraint not met in plan '" << plan << "', missing " << c << "\n";
            return false;
        }
    }
    return true;
}

char find_satisfied(array<Constraint, 26> const &constraints, string const&plan, string const&goal)
{
    cout << "Finding next step from plan '" << plan << "', already done: '" << goal << "'\n";

    for (char c : plan)
    {
        if (satisfied(constraints[c - 'A'], goal))
            return c;
    }

    return 0;
}

int main()
{
    array<Constraint, 26> constraints {};
    size_t plansize = 26;
    size_t baseline = 60;

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
    while(plan.size() != plansize)
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

    /************************************/
    /************************************/
    /************************************/
    string done;
    Task workers[5];
    size_t duration = 0;

    while (done.size() != plansize)
    {
        ++duration;
        for(Task &task : workers)
            if (task.time_left != 0) --task.time_left;

        for (Task &task : workers)
        {
            if (task.time_left == 0 && task.step != '\0')
            {
                done += task.step;
                task.step = '\0';
            }
        }

        for (Task &task : workers)
        {
            char next = find_satisfied(constraints, plan, done);
            if (next == 0) break;

            if (task.time_left == 0)
            {
                if (plan.size() > 0 && satisfied(constraints[next - 'A'], done))
                {
                    task.time_left = baseline + (next - 'A') + 1;
                    task.step = next;
                    plan.erase(plan.find(next), 1);
                }
            }
        }

        cout << "Plan / Done: '" << plan << "' / '" << done << "'\n";
        cout << "Workers on: \n";
        for (Task &task : workers)
        {
            cout << "     Step: " << (task.step == '\0' ? '-' : task.step) << "\n";
            cout << "     Time: " << task.time_left << "\n";
        }
        cout << "\n";
        // this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    cout << "Total time: " << duration << "s \n";
}