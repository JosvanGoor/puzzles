#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector<int> numbers;
    ifstream in("input.txt");

    while (true)
    {
        int tmp;
        in >> tmp;

        if (!in)
            break;

        numbers.push_back(tmp);
        cout << "read " << tmp << "\n";
    }

    cout << "Read " << numbers.size() << " numbers.\n";

    for (size_t outer = 0; outer < numbers.size(); ++outer)
    {
        for (size_t inner = outer + 1; inner < numbers.size(); ++inner)
        {
            for (size_t innest = inner + 1; innest < numbers.size(); ++innest)
            {
                if (numbers[outer] + numbers[inner] + numbers[innest] == 2020)
                    cout << "Answer: " << numbers[outer] * numbers[inner] * numbers[innest] << "\n";

            }
        }
    }



}