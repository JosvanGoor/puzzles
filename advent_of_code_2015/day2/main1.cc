#include <iostream>
#include <string>

using namespace std;

struct Present
{
    size_t length;
    size_t width;
    size_t height;

    size_t extra_wrap()
    {
        return min(length * width, min(length * height, width * height));
    }

    size_t wrap_required()
    {
        return 2 * length * width
            + 2 * width * height
            + 2 * height * length
            + extra_wrap();
    }

    size_t bow_size()
    {
        return length * width * height;
    }

    size_t ribbon_required()
    {
        size_t ribbon = min(length + width, min(length + height, width + height)) * 2;
        return ribbon + bow_size();
    }
};

istream &operator>>(istream& in, Present &present)
{
    in >> present.length;
    in.ignore(1); // ignore 'x'.
    in >> present.width;
    in.ignore(1); // ignore 'x'.
    in >> present.height;

    return in;
}

int main()
{
    size_t total_wrap = 0;
    size_t total_ribbon = 0;
    Present present;

    while(!cin.eof())
    {
        cin >> present;
        total_wrap += present.wrap_required();
        total_ribbon += present.ribbon_required();
    }

    cout << "Total wrap required: " << total_wrap << "\n";
    cout << "Total ribbon required: " << total_ribbon << "\n";
}