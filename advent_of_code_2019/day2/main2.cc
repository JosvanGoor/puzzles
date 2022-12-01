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

int run_program(vector<int> program, int noun = 12, int verb = 2)
{
    cout << "running program!\n";
    size_t instruction = 0;

    program[1] = noun;
    program[2] = verb;

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
                return program[0];
        }
    }
}

int main(int argc, char *argv[])
{
    vector<int> program = read_input();
    int target_output = 19690720;

    for (int noun = 0; noun < 100; ++noun)
    {
        cout << "\rIteration: " << noun << " / 100";
        for (int verb = 0; verb < 100; ++verb)
        {
            int result = run_program(program, noun, verb);
            
            if (result == target_output)
            {
                cout << "Noun: " << noun << "\n";
                cout << "Verb: " << verb << "\n";
                cout << "Answer: " << (100 * noun + verb) << "\n";
                return 0;
            }
        }
    }
}