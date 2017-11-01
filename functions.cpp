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
        delete playerArray;
        int numberOfPlayers;                                //Lager array for spillerene
        playerArray = createPlayers(&numberOfPlayers);      //create players tar numberOfPlayers, gir den ein value og lager spillerene

        for(int i = 1; i < 13; i++)                 //satte i = 1 for å stemme med rundenummer
        {
            displayPlayChart();

            std::cout << "Round " << i << ":" << std::endl;

            for(int j = 0; j < numberOfPlayers; j++)
            {
                for(int l = 0; l < 5; l++)
                {
                    playerArray[j].reroll[l] = true;
                }
            }
            turn(playerArray, numberOfPlayers, i);  //setter alle spillerene inn i ein runde

            displayScore(playerArray, numberOfPlayers);
        }

        displayScore(playerArray, numberOfPlayers, true);

        std::cout << "Would you like to play again?" << std::endl;
        inPlay = yesNoMenu();

        delete playerArray;
    }
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
            if(dice[j] < dice[i])                       //bruker selection sort for å sortere high til low
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
        std::cout << player[i].name << "'s turn" << std::endl;

        for(int j = 0; j < 3; j++)
        {
            std::cout << "Throw " << j + 1 << ":" << std::endl;
            rollDice(player[i].heldDice, player[i].reroll);

            if(j < 2)                                       //tester om det er siste kast
                rerollManager(&player[i]);
            else
            {
                for(int i = 0; i < 5; i++)
                {
                    std:: cout << static_cast<char>('A' + i) << ": " << player->heldDice[i] << std::endl;
                }
                std::cout << std::endl;
            }
        }

        score(player[i].heldDice, turn, &player[i].points);
    }
}

void score(int dice[], int round, int* score)
{
    sort(dice);                                             //sorterer terningene for dem fleste testene krever at dem er sortert

    switch(round)
    {
    case 1:
    case 2:
    case 3:                                     //runde 1-6 bruker samme metode, men annet tall
    case 4:
    case 5:
    case 6:
        *score += testDigits(dice, round);
        break;
    case 7:
        *score += testPairs(dice);
        break;
    case 8:
        *score += testTriplets(dice);                           //Test for dem forskjellige casene
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
        if(dice[i] == digit)                    //Går gjennom alle verdiene i dice og sjekker om dem er lik digit, setter total verdien inn i sum
            sum += dice[i];
    }

    return sum;
}

int testPairs(int dice[])
{
    int sum{0};

    for(int i = 0; i < 4; i++)
    {
        if(dice[i] == dice[i + 1])                   //Sjekker oppover fra 0 om to tall er like, om eit par blir funnet hopper den eit steg ekstra for å ikkje
        {                                            //telle tre like som 2 par. Legger verdien av parene inn i sum
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
        if(dice[i] == dice[i + 1] && dice[i] == dice[i + 2])                //samme prosedyre som par, men annen sjekk
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

    for(int i = 0; i < 2; i++)                                          //samme prosedyre som par og triplet, men annen sjekk
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
    int sum{0};                                                 //same, same, but different

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
        for(int i = 0; i < 5; i++)                                              //sjekker om dem to første er like, so om dem to første er lik med den tredje, deretter om dem to siste er like
        {                                                                       //Om ikkje sjekkes dem tre siste om dem er like.
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
        for(int i = 0; i < 5; i++)                  //sjekker om tallene former ein rekke, om den gjør settes alle verdiene inn i sum
        {
            sum += dice[i];
        }
    }
    return sum;
}

void displayScore(players* player, int num, bool calculateWinner)
{
    int score[num];
    std::string name[num];              //brukes til sortering for å ikkje rote med spillerrekkefølgen

    for(int i = 0; i < num; i++)
    {
        score[i] = player[i].points;
        name[i] = player[i].name;
    }
    sortScoreBoard(score, name, num);       //sorterer score og name sånn at den med mest poeng havner øverst


    if(calculateWinner)         //vist true blir sendt inn som parameter vil den kalkulere vinneren
    {
        bool sharedFirstPlace = true;

        std::cout << "The winner is " << name[0];

        for(int i = 0; i < num && sharedFirstPlace; i++)
        {
            if(score[i] != score[i + 1])                    //sjekker om det er delt førsteplass.
                sharedFirstPlace = false;
            else
            {
                std::cout << " and " << name[i + 1];
            }
        }
        std::cout << " with " << score[0] << " points!" << std::endl;
    }
    else
    {
        std::cout << "Current standing: " << std::endl << std::endl;

        for(int i = 0; i < num; i++)
        {
            std::cout << i + 1 << ": " << name[i] << " - " << score[i] << std::endl << std::endl;       //printer ut scoreboarden
        }

    }
}

void sortScoreBoard(int score[], std::string name[], int num)
{
    for(int i = 0; i < num; i++)
    {
        for(int j = i; j < num; j++)
        {
            if(score[j] > score[i])
            {
                std::swap(score[j], score[i]);              //selection sort for å plassere høyeste scoren øverst
                std::swap(name[j], name[i]);
            }
        }
    }
}

bool yesNoMenu()
{
    char choice;

    while(true)
    {
        std::cout << "Y/N";         //simpel ja/nei meny som returnerer true eller false

        std::cin >> choice;

        cinSanitizer();

        switch(choice)
        {
        case 'y':
        case 'Y':
            return true;
            break;
        case 'n':
        case 'N':
            return false;
        }
    }
}

void displayPlayChart()
{
    std::cout << std::endl
              << "Round 1: Ones" << std::endl
              << "Round 2: Twos" << std::endl
              << "Round 3: Threes" << std::endl
              << "Round 4: Fours" << std::endl
              << "Round 5: Fives" << std::endl
              << "Round 6: Sixes" << std::endl
              << "Round 7: Pairs" << std::endl                                  //Viser kva det spilles om i rundene
              << "Round 8: Triplets" << std::endl
              << "Round 9: Quadrets" << std::endl
              << "Round 10: Yatzy" << std::endl
              << "Round 11: Full house" << std::endl
              << "Round 12: straight" << std::endl << std::endl;

}
