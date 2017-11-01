#include <iostream>
#include <cstdlib>
#include <limits>
#include "functions.h"

void rollDice(int dice[5], bool reroll[5])
{
    for(int i = 0; i < 5; i++)
    {
        if(reroll[i])
            dice[i] = rand()%6 + 1;
    }
}

void play()
{
    bool inPlay = true;

    while(inPlay)
    {
        players* playerArray = new players;
        int numberOfPlayers;                                //lager dynamisk array for spillerene
        playerArray = createPlayers(&numberOfPlayers);      //create players tar numberOfPlayers, gir den ein value og lager spillerene

        for(int i = 1; i < 13; i++)                 //satte i = 1 for å stemme med rundenummer
        {
            std::cout << "Round " << i << ":" << std::endl;
            for(int j = 0; j < numberOfPlayers; j++)
            {
                for(int l = 0; l < 5; l++)
                {
                    playerArray[j].reroll[l] = true;
                }
            }
            turn(playerArray, numberOfPlayers, i);  //setter alle spillerene inn i ein runde
        }

        inPlay = false;
    }

    std::cout << "Testy 2: The second coming" << std::endl;         //test line, plz ignore
}

players* createPlayers(int* num)
{
    do{
        std::cout << "How many are playing? MAX 6" << std::endl;                    //Tror maks 6 spillere er standard for Yatzy

        *num = 0;

        std::cin >> *num;                       //assigner value til numberOfPlayers

        cinSanitizer();

        if(!(0 < *num && *num <= 6))
            std::cout << "Not a valid number. Pick again" << std::endl;             //redo vist input ikkje er valid

    }while(!(0 < *num && *num <= 6));

    players* playerArray = new players [*num];

    playerArray = namePlayers(playerArray, num);        //Navngir spillerene

    return playerArray;
}

players* namePlayers(players* playerArray, int* num)
{
    for(int i = 0; i < *num; i++)
    {
        std::cout << "What is player " << i + 1 << "'s name?" << std::endl;     //spør om spiller i + 1 sitt navn
        std::cin >> playerArray[i].name;
        cinSanitizer();
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

void rerollManager(players* player)
{
    bool choiceInTheMaking = true;

    char choice{0};

    while(choiceInTheMaking)
    {
        for(int i = 0; i < 5; i++)
        {
            std:: cout << static_cast<char>('A' + i) << ": " << player->heldDice[i] << " - ";           //printer ut terningene

            if(player->reroll[i])
                std::cout << "No";
            else                                    //printer dersom terningen skal beholder eller ikkje
                std::cout << "Yes";

            std::cout << std::endl;
        }
        std::cout << "Which dice will you keep?" << "(type f for done)" << std::endl;

        std::cin >> choice;         //spilleren velger terningene som skal beholdes

        cinSanitizer();

        switch(choice)
        {
        case 'a':
        case 'A':
            player->reroll[0] = !player->reroll[0];
            break;
        case 'b':
        case 'B':
            player->reroll[1] = !player->reroll[1];
            break;
        case 'c':
        case 'C':
            player->reroll[2] = !player->reroll[2];                         //toggler reroll
            break;
        case 'd':
        case 'D':
            player->reroll[3] = !player->reroll[3];
            break;
        case 'e':
        case 'E':
            player->reroll[4] = !player->reroll[4];
            break;
        case 'f':
        case 'F':
            choiceInTheMaking = false;
            break;
        default:
            std::cout << "Unknown command!" << std::endl;
        }
    }
}

void cinSanitizer()
{
    if(std::cin.fail())                                                         //sjekker om cin feilet
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');     //tømmer input på cin fram til '\n'
    }
}

void turn(players* player, int num, int turn)
{
    for(int i = 0; i < num; i++)
    {
        bool rerollDone{false};

        std::cout << player[i].name << "'s turn" << std::endl;

        for(int j = 0; j < 3 && !rerollDone; j++)
        {
            std::cout << "Throw " << j + 1 << ":" << std::endl;
            rollDice(player[i].heldDice, player[i].reroll);

            if(i < 2 && !rerollDone)                                       //tester om det er siste kast
                rerollManager(&player[i]);
        }

        score(player[i].heldDice, turn, &player[i].points);
    }
}


void score(int dice[], int round, int* score)
{
    sort(dice);

    switch(round)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
        *score += testDigits(dice, round);
        break;
    case 7:
        *score += testPairs(dice);
        break;
    case 8:
        *score += testTriplets(dice);
        break;
    case 9:
        *score += testQuadrets(dice);
        break;
    case 10:
        *score += testYatzy(dice);
        break;
    case 11:
        *score += testFullHouse(dice);
        break;
    case 12:
        *score += testStraight(dice);
        break;
    }

    std::cout << "Current score: " << *score << std::endl;
}

int testDigits(int dice[], int digit)
{
    int sum{0};

    for(int i = 0; i < 5; i++)
    {
        if(dice[i] == digit)
        sum += dice[i];
    }

    return sum;
}

int testPairs(int dice[])
{
    sort(dice);

    int sum{0};

    for(int i = 0; i < 4; i++)
    {
        if(dice[i] == dice[i + 1])
        {
            for(int j = 0; j < 2; j++)
            {
                sum += dice[i + j];
            }

            i++;
        }
    }
    return sum;
}

int testTriplets(int dice[])
{
    sort(dice);

    int sum{0};

    for(int i = 0; i < 3; i++)
    {
        if(dice[i] == dice[i + 1] && dice[i] == dice[i + 2])
        {
            for(int j = 0; j < 3; j++)
            {
                sum += dice[i + j];
            }

            i += 2;
        }
    }
    return sum;
}

int testQuadrets(int dice[])
{
    int sum{0};

    for(int i = 0; i < 2; i++)
    {
        if(dice[i] == dice[i + 1] && dice[i] == dice[i + 2] && dice[i] == dice[i +3])
        {
            for(int j = 0; j < 4; j++)
            {
                sum += dice[i + j];
            }

            i++;
        }
    }
    return sum;
}

int testYatzy(int dice[])
{
    int sum{0};

    if(dice[0] == dice[1] && dice[0] == dice[2] && dice[0] == dice[3] && dice[0] == dice[4])
        for(int i = 0; i < 5; i++)
        {
            sum += dice[i];
        }
    return sum;
}

int testFullHouse(int dice[])
{
    int sum{0};

    if(dice[0] == dice[1] && ((dice[1] == dice[2] && dice[3] == dice[4]) || (dice[2] == dice[3] && dice[3] == dice[4])))
            {
                for(int i = 0; i < 5; i++)
                {
                    sum += dice[i];
                }
            }
    return sum;
}

int testStraight(int dice[])
{
    int sum{0};

    if(dice[0] == (dice[1] - 1) && dice[0] == (dice[2] - 2) && dice[0] == (dice[3] - 3) && dice[0] == (dice[4] - 4))
    {
        for(int i = 0; i < 5; i++)
        {
            sum += dice[i];
        }
    }
    return sum;
}
