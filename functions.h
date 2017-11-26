#ifndef FUNCTIONS_H
#define FUNCTIONS_H

struct Players
{
    int heldDice[5] = {0, 0, 0, 0, 0};
    bool reroll[5] = {1, 1, 1, 1, 1};
    int points{0};
    std::string name;
};

void rollDice(int dice[], bool reroll[]);
void play();
Players* createPlayers(int* num);
void namePlayers(Players* playerArray, int* num);
void sort(int* dice);
void rerollManager(Players* player);
void cinSanitizer();
void turn(Players* player, int num, int turn);
void score(int dice[], int round, int* score);
int testDigits(int dice[], int digit);
int testPairs(int dice[]);
int testTriplets(int dice[]);
int testQuadrets(int dice[]);
int testYatzy(int dice[]);
int testFullHouse(int dice[]);
int testStraight(int dice[]);
void displayScore(Players *player, int num, bool calculateWinner = false);
void sortScoreBoard(int score[], std::string name[], int num);
bool yesNoMenu();
void displayPlayChart();

#endif // FUNCTIONS_H
