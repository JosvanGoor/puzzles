#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* Slow-as-fuck solution:

    $ time ./a.out < input.in
    Num players: 468
    Last marble: 7184300
    Best player had a score of 3156297594
    ./a.out < input.in  5143.54s user 1.02s system 99% cpu 1:25:53.91 total

*/

struct Game
{
    size_t num_players;
    size_t last_marble;
};

istream &operator>>(istream &in, Game &game)
{
    cin >> game.num_players;
    cin.ignore(31); // ignore ' players; last marble is worth '.
    cin >> game.last_marble;
    cin.ignore(8); // ignore '  points\n'

    return in;
}

size_t index(size_t main, size_t size)
{
    main += 2;
    main = main % size;
    return main;
}

void print_gamestate(size_t round, vector<size_t> const &game, size_t main)
{
    cout << setw(7) << ("["s + to_string(round) + "]: "s);
    for (size_t idx = 0; idx != game.size(); ++idx)
    {
        if (idx == main)
            cout << setw(5) << ("("s + to_string(game[idx]) + ")"s);
        else
            cout << setw(5) << game[idx];
    }
    cout << "\n";
}

size_t insert_marble(vector<size_t> *game, size_t main, size_t marble)
{
    size_t before = (main + 2) % game->size();

    if (before == 0)
    {
        game->push_back(marble);
        return game->size() - 1;
    }

    game->insert(game->begin() + before, marble);
    return before;
}

size_t bonus_marble(size_t main, size_t size)
{
    if (main < 7)
        return size - (7 - main);
    
    return main - 7;
}

int main()
{
    Game game;
    cin >> game;

    cout << "Num players: " << game.num_players << "\n";
    cout << "Last marble: " << game.last_marble << "\n";

    size_t main_marble = 0;
    
    vector<size_t> players;
    players.resize(game.num_players, 0);

    vector<size_t> marbles { 0 };
    // print_gamestate(0, marbles, main_marble);

    for (size_t idx = 1; idx != game.last_marble + 1; ++idx)
    {
        cout << "Progress: " << idx / static_cast<float>(game.last_marble) * 100 << "\r";

        if (idx % 23 == 0) //special case
        {
            size_t player = (idx - 1) % game.num_players;
            players[player] += idx;

            main_marble = bonus_marble(main_marble, marbles.size());
            players[player] += marbles[main_marble];
            marbles.erase(marbles.begin() + main_marble);
        }
        else
        {
            main_marble = insert_marble(&marbles, main_marble, idx);
        }
        // print_gamestate(idx, marbles, main_marble);
    }

    size_t best_player = 0;
    for (size_t idx = 1; idx < players.size(); ++idx)
    {
        if (players[best_player] < players[idx])
            best_player = idx;
    }

    cout << "Best player had a score of " << players[best_player] << "\n";
}