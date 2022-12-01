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

    vector<vector<bool>> lights;
    lights.resize(1000, vector<bool>(1000, false));

    for (Instruction const &instr : instructions)
    {
        for (size_t idx = instr.from.x; idx <= instr.through.x; ++idx)
        {
            for (size_t idy = instr.from.y; idy <= instr.through.y; ++idy)
            {
                switch(instr.action)
                {
                    case TURN_OFF:
                        lights[idx][idy] = false;
                    break;

                    case TURN_ON:
                        lights[idx][idy] = true;
                    break;

                    case TOGGLE:
                        lights[idx][idy] = !lights[idx][idy];
                    break;
                }
            }
        }
    }

    size_t lights_on = 0;
    for (size_t idx = 0; idx != lights.size(); ++idx)
    {
        for (size_t idy = 0; idy != lights[idx].size(); ++idy)
        {
            if (lights[idx][idy])
                ++lights_on;
        }
    }

    cout << "There are " << lights_on << " lights turned on!\n";
}