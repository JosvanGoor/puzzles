#include <iostream>
#include <vector>

using namespace std;

vector<int> read_input()
{
    vector<int> rval;
    int buffer;
    char comma;

    while (cin)
    {
        cin >> buffer;
        rval.push_back(buffer);
        cin >> comma;
    }

    return rval;
}

int main(int argc, char *argv[])
{
    vector<int> program = read_input();
    size_t instruction = 0;

    // fix according to assignment
    program[1] = 12;
    program[2] = 2;

    while(true)
    {
        switch(program[instruction++])
        {
            case 1:
            {
                size_t lhs = program[instruction++];
                size_t rhs = program[instruction++];
                size_t result = program[instruction++];
                program[result] = program[lhs] + program[rhs];
            }
            break;

            case 2:
            {
                size_t lhs = program[instruction++];
                size_t rhs = program[instruction++];
                size_t result = program[instruction++];
                program[result] = program[lhs] * program[rhs];
            }
            break;

            case 99:
                cout << "Result: " << program[0] << "\n";
                return 0;
        }
    }
    
}