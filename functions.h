#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct players
{
    int heldDice[5]{0, 0, 0, 0, 0};
    bool reroll[5]{1, 1, 1, 1, 1};
    int points{0};
    std::string name;
};

void rollDice(players *player);
void play();
players* createPlayers(int *num);
players* namePlayers(players* playerArray, int *num);
void sort(int* dice);

#endif // FUNCTIONS_H
