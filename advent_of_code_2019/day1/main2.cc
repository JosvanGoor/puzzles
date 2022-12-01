#include <iostream>

using namespace std;

int required_fuel(int mass)
{
    int fuel = (mass / 3) - 2;

    if (fuel <= 0)
        return 0;
    
    return fuel + required_fuel(fuel);
}

int main(int argv, char **argc)
{
    int sum = 0;

    while (!cin.eof())
    {
        int mass;
        cin >> mass;
        sum += required_fuel(mass);
        // cout << mass << " requires " << required_fuel(mass) << "\n";

    }

    cout << "Total required fuel: " << sum << "\n";
}