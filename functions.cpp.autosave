#include <iostream>
#include <cstdlib>
#include <limits>
#include "functions.h"

void rollDice(players* player)
{
    for(int i = 0; i < 5; i++)
    {
        if(player->reroll[i])
            player->heldDice[i] = rand()%6 + 1;
    }
}

void play()
{
    bool inPlay = true;

    while(inPlay)
    {
        players* playerArray = new players;
        int numberOfPlayers;
        playerArray = createPlayers(&numberOfPlayers);

        rollDice(&playerArray[0]);

        inPlay = false;
    }

    std::cout << "Testy 2: The second coming" << std::endl;
}

players* createPlayers(int *num)
{
    do{
        std::cout << "How many are playing? MAX 6" << std::endl;

        std::cin >> *num;

        if(std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        if(!(0 < *num && *num <= 6))
            std::cout << "Not a valid number. Pick again" << std::endl;

    }while(!(0 < *num && *num <= 6));

    players* playerArray = new players [*num];

    playerArray = namePlayers(playerArray, num);

    return playerArray;
}

players* namePlayers(players* playerArray, int *num)
{
    for(int i = 0; i < *num; i++)
    {
        std::cout << "What is player " << i + 1 << "'s name?" << std::endl;
        std::cin >> playerArray[i].name;
    }

    return playerArray;
}

void sort(int* dice)
{
    for(int i = 0; i < 5; i++)
    {
        for(int j = i; j < 5; j++)
        {
            if(dice[j] < dice[i])
                std::swap(dice[i], dice[j]);
        }
    }
}
