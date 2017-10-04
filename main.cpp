#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct players
{
    int dice[5]{0, 0, 0, 0, 0};
    int points{0};
};

void rollDice(players* player);

int main()
{
    srand(time(NULL));

    players player;

    rollDice(&player);

    for(int i = 0; i < 5; i++)
    {
        cout << player.dice[i] << endl;
    }
}

void rollDice(players* player)
{
    for(int i = 0; i < 5; i++)
    {
        player->dice[i] = (rand()%6) + 1;
    }
}
