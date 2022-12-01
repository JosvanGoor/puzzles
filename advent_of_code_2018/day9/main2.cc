#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
    $ time ./a.out < input.in 
    Num players: 468
    Last marble: 7184300
    Highest reached score: 3156297594
    ./a.out < input.in  0.16s user 0.05s system 99% cpu 0.203 total

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

struct List
{
    size_t marble;
    List *next;
    List *previous;

    List(size_t num)
    : marble(num), next(this), previous(this)
    { }

    List *rotate(int direction)
    {
        List *rval = this;

        if (direction > 0)
        {
            for (; direction--; )
                rval = rval->next;
        }
        else 
        {
            direction *= -1;
            for (; direction--; )
                rval = rval->previous;
        }

        return rval;
    }

    List* insert_after(List *entry) //assume single entry
    {
        entry->next = next;
        entry->next->previous = entry; 
        entry->previous = this;
        next = entry;

        return entry;
    }

    //returns next in list. or nullptr when list size == 1
    List* remove_current()
    {
        if (next == this)
        {
            delete this;
            return nullptr;
        }

        next->previous = previous;
        previous->next = next;

        List *rval = next;
        delete this;
        return rval;
    }

    void print_list()
    {
        List *current = next;
        cout << setw(5) << marble;

        while (current != this)
        {
            cout << setw(5) << current->marble;
            current = current->next;
        }
    }
};

int main()
{

    Game game;
    cin >> game;

    cout << "Num players: " << game.num_players << "\n";
    cout << "Last marble: " << game.last_marble << "\n";

    List *root = new List(0);
    List *main = root;

    vector<size_t> players;
    players.resize(game.num_players, 0);

    for (size_t idx = 1; idx < game.last_marble + 1; ++idx)
    {
        if (idx % 23 == 0)
        {
            size_t player = (idx + 1) % game.num_players;
            players[player] += idx;

            main = main->rotate(-7); //?
            players[player] += main->marble;
            main = main->remove_current();
        }
        else
        {
            main = main->rotate(1)->insert_after(new List(idx));
        }
    }

    size_t player = 0;
    for (size_t idx = 0; idx < game.num_players; ++idx)
    {
        if (players[player] < players[idx])
            player = idx;
    }

    cout << "Highest reached score: " << players[player] << "\n";

    while(root)
        root = root->remove_current();

}