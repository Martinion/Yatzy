#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct players
{
    int heldDice[5]{0, 0, 0, 0, 0};
    bool reroll[5]{1, 1, 1, 1, 1};
    int points{0};
    std::string name;
};

void rollDice(int dice[], bool reroll[]);
void play();
players* createPlayers(int* num);
players* namePlayers(players* playerArray, int* num);
void sort(int* dice);
void rerollManager(players* player);
void cinSanitizer();
void turn(players* player, int num, int turn);
void score(int dice[], int round, int* score);
int testDigits(int dice[], int digit);
int testPairs(int dice[]);
int testTriplets(int dice[]);
int testQuadrets(int dice[]);
int testYatzy(int dice[]);
int testFullHouse(int dice[]);
int testStraight(int dice[]);

#endif // FUNCTIONS_H
