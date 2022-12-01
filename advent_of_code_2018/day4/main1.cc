#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct Event
{
    tm time;
    string event;
};

istream &operator>>(istream &in, Event &event)
{
    char toss;
    
    in >> toss; // toss '['
    in >> event.time.tm_year;
    event.time.tm_year -= 1900;
    in >> toss; // toss '-'
    in >> event.time.tm_mon;
    in >> toss; // toss '-'
    in >> event.time.tm_mday;

    in >> event.time.tm_hour;
    in >> toss; // toss ':'
    in >> event.time.tm_min;
    in >> toss; // toss ']'

    getline(cin, event.event);
    return in;
}

ostream &operator<<(ostream &out, Event const &event)
{
    out << "Event: \n";
    out << "    " << put_time(&event.time, "%c") << "\n";
    out << "     - " << event.event << "\n";
    return out;
}

int main()
{
    vector<Event> events;
    map<int, int[60]> guards;

    cout << setfill(' ');

    while(!cin.eof())
    {
        Event event{};
        cin >> event;
        events.push_back(event);
    }

    std::sort(events.begin(), events.end(), 
        [](Event &lhs, Event &rhs)
        {
            time_t l_time = mktime(&lhs.time);
            time_t r_time = mktime(&rhs.time);

            return l_time < r_time;
        });

    int current_id;
    for (Event const &event : events)
    {
        size_t numstart = event.event.find("#");
        if (numstart != string::npos)
        {
            size_t end = event.event.find(" ", numstart);
            current_id = stoi(event.event.substr(numstart + 1, end - numstart - 1));
        }

        else if (event.event.find("asleep") != string::npos)
        {
            for (size_t idx = event.time.tm_min; idx != 60; ++idx)
                ++guards[current_id][idx];
        }

        else if (event.event.find("wakes") != string::npos)
        {
            for (size_t idx = event.time.tm_min; idx != 60; ++idx)
                --guards[current_id][idx];
        }
    }
    
    size_t max_id = 0;
    size_t sleeper = 0;
    
    // cout << " Guard ID   Minute\n";
    // cout << "                      1         2         3         4         5\n";
    // cout << "            012345678901234567890123456789012345678901234567890123456789\n";
    cout << "             ";
    for (size_t idx = 0; idx != 60; ++idx)
        cout << setw(3) << idx;
    cout << " | total\n";

    for (auto const &[id, sleep] : guards)
    {
        cout << "Guard " << setw(5) << id << ": ";
        size_t total = 0;

        for (int num : sleep)
        {
            cout << setw(3) << num;
            total += num;
        }
        cout << " | " << total << "\n";


        if (total > sleeper)
        {
            max_id = id;
            sleeper = total;
        }
    }

    cout << "Max sleeper: " << max_id << "\n";
    
    size_t min_id = 0;
    sleeper = 0;
    for (size_t idx = 0; idx != 60; ++idx)
    {
        if (guards[max_id][idx] > sleeper)
        {
            sleeper = guards[max_id][idx];
            min_id = idx;
        }
    }

    cout << "Slept most in minute " << min_id << ", for " << sleeper << " minutes.\n";

    sleeper = 0;
    min_id = 0;
    size_t minute = 0;

    for (auto const &[id, sleep] : guards)
    {
        for (size_t idx = 0; idx != 60; ++idx)
        {
            if (sleep[idx] >= sleeper)
            {
                sleeper = sleep[idx];
                min_id = id;
                minute = idx;
            }
        }
    }

    cout << "Guard " << min_id << " is most frequently asleep on minute ";
    cout << minute << "\n";
    cout << sleeper * minute << "\n";

}