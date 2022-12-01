#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Claim
{
    size_t id;
    size_t px;
    size_t py;
    size_t width;
    size_t height;
};

istream &operator>>(istream &in, Claim &claim)
{
    // reading into char in favor if in.ignore(), to automatically
    // toss any present whitespace.
    char at; 

    cin >> at; //ignore '#'
    in >> claim.id;

    in >> at; //ignore '@'
    in >> claim.px;
    cin >> at; //ignore ','
    in >> claim.py;

    in >> at; //ignore ':'
    in >> claim.width;
    in >> at; //ignore 'x'
    in >> claim.height;

    return in;
}

void layout_claim(vector<vector<int>> &canvas, Claim const &claim)
{
    size_t end_x = claim.px + claim.width;
    size_t end_y = claim.py + claim.height;

    for (size_t px = claim.px; px != end_x; ++px)
    {
        for (size_t py = claim.py; py != end_y; ++py)
            ++canvas[px][py];
    }
}

bool overlaps(vector<vector<int>> &canvas, Claim const &claim)
{
    size_t end_x = claim.px + claim.width;
    size_t end_y = claim.py + claim.height;

    for (size_t px = claim.px; px != end_x; ++px)
    {
        for (size_t py = claim.py; py != end_y; ++py)
        {
            if (canvas[px][py] != 1)
                return true;
        }
    }

    return false;
}

int main()
{
    size_t total_width = 0;
    size_t total_height = 0;
    vector<Claim> claims;
    vector<vector<int>> canvas;
    
    while (!cin.eof())
    {
        Claim claim;
        cin >> claim;

        total_width = max(total_width, claim.px + claim.width);
        total_height = max(total_height, claim.py + claim.height);

        claims.push_back(claim);
    }

    canvas.resize(total_width, vector<int>(total_height, 0));
    for (Claim const &claim : claims)
        layout_claim(canvas, claim);

    size_t overlap = 0;
    for (size_t py = 0; py < total_height; ++py)
    {
        for (size_t px = 0; px < total_width; ++px)
        {
            if (canvas[px][py] > 1)
                ++overlap;
        }
    }

    for (size_t idx = 0; idx != claims.size(); ++idx)
    {
        if (!overlaps(canvas, claims[idx]))
            cout << "No overlap for " << idx << "\n";
    }
    
}