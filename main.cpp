#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct players
{
    int heldDice[5]{0, 0, 0, 0, 0};
    int points{0};
};

void rollDies(players* player);

int main()
{
    srand(time(NULL));

    players player;

    rollDies(&player);


}

void rollDies(players* player)
{
    int dice[6];

    for(int i = 0; i < 5; i++)
    {
        dice[i] = (rand()%6) + 1;
    }

    for(int i = 0; i < 5; i++)
    {
        cout << i << ": " << dice[i] << endl;
    }

    cout << "Which dies will you keep? choose -1 to quit" << endl;

    int choice;

    do
    {
        cin >> choice;

        if(choice != -1){
            if(dice[choice] == 0)
                cout << "Not applicable" << endl;

            int i{-1};

            do
            {
                i++;

                if(player->heldDice[i] == 0)
                {
                    player->heldDice[i] = dice[choice];
                    dice[choice] = 0;
                }

            }while(dice[choice] != 0);
        }
    }while(choice != -1);
}
