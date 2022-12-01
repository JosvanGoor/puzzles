#include <iostream>

using namespace std;

int required_fuel(int mass)
{
    return (mass / 3) - 2;
}

int main(int argv, char **argc)
{
    int sum = 0;

    while (!cin.eof())
    {
        int mass;
        cin >> mass;

        cout << mass << " requires " << required_fuel(mass) << "\n";

        sum += required_fuel(mass);
    }

    cout << "Total required fuel: " << sum << "\n";
}