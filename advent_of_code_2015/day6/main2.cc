#include "main.ih"

int main()
{
    vector<Instruction> instructions;

    while(!cin.eof())
    {
        Instruction instr;
        cin >> instr;

        instructions.push_back(instr);
        cout << "Instruction set " << instr.action << "\n";
        cout << "    from: [" << instr.from.x << ", " << instr.from.y << "]\n";
        cout << "    througn: [" << instr.through.x << ", " << instr.through.y << "]\n";
    }

    vector<vector<int>> lights;
    lights.resize(1000, vector<int>(1000, 0));

    for (Instruction const &instr : instructions)
    {
        for (size_t idx = instr.from.x; idx <= instr.through.x; ++idx)
        {
            for (size_t idy = instr.from.y; idy <= instr.through.y; ++idy)
            {
                switch(instr.action)
                {
                    case TURN_OFF:
                        lights[idx][idy] 
                            = lights[idx][idy] ? lights[idx][idy] - 1 : 0;
                    break;

                    case TURN_ON:
                        lights[idx][idy] += 1;
                    break;

                    case TOGGLE:
                        lights[idx][idy] += 2;
                    break;
                }
            }
        }
    }

    size_t brightness = 0;
    for (size_t idx = 0; idx != lights.size(); ++idx)
    {
        for (size_t idy = 0; idy != lights[idx].size(); ++idy)
            brightness += lights[idx][idy];
    }

    cout << "Total brightness: " << brightness << "\n";
}