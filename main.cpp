#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct players
{
    int heldDice[5]{0, 0, 0, 0, 0};
    bool reroll[5]{1, 1, 1, 1, 1};
    int points{0};
};

void rollDice(players *player);

int main()
{
    srand(time(NULL));

    players player1;

    rollDice(&player1);

    for(int i = 0; i < 5; i++)
    {
        cout << player1.heldDice[i] << endl;
    }

    return 0;
}

void rollDice(players* player)
{
    for(int i = 0; i < 5; i++)
    {
        if(player->reroll[i])
            player->heldDice[i] = rand()%6 + 1;
    }
}
