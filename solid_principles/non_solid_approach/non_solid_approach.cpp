#include <iostream>
#include <map>
#include <random>

int RollDice()
{
    static std::random_device rd;  // Non-deterministic seed
    static std::mt19937 gen(rd()); // Mersenne Twister engine
    static std::uniform_int_distribution<> dis(1, 6); // Range [1, 6]
    return dis(gen);
}

int main()
{
    std::map<int, int> mSnakes;
    std::map<int, int> mLadders;

    /*Snakes will store start and end point of a snake*/
    mSnakes[99] = 10;
    mSnakes[92] = 55;
    mSnakes[77] = 32;
    mSnakes[44] = 25;
    mSnakes[25] = 3;

    /*mLadders will store start and end point of a ladder*/
    mLadders[3] = 24;
    mLadders[21] = 43;
    mLadders[47] = 87;
    mLadders[75] = 95;

    /*player1 & player2 will track player's position */
    int nPlayersPosition[2] = {0,0};

    std::cout << "=== Snake and Ladder Game ===\n";

    int nRound = 0;
    int nCurrentPlayer = 0;
    while(true)
    {
        std::cout << "  === Round "<<++nRound<<" begin's. Press ENTER to play ===\n";
        std::cin.get();

        std::cout<< "=== Player"<< nCurrentPlayer<< "'s turn ===\n";
        int nPlayerPos = nPlayersPosition[nCurrentPlayer];
        int nRandOutcome = RollDice();
        std::cout<<"randon outcome : "<<nRandOutcome <<"\n"; 
        nPlayerPos += nRandOutcome;

        if(nPlayerPos == 100)
        {
            std::cout << "Player"<<nCurrentPlayer<<" reached at 100 ! \n";
            std::cout << "Player"<<nCurrentPlayer<<" Won !!!!!!!! \n";
            break;
        }
        else if (nPlayerPos > 100)
        {
            std::cout << "Player"<<nCurrentPlayer<<" can't move! wait for next round";
        }
        else
        {
            std::cout << "Player"<<nCurrentPlayer<<" move at "<< nPlayerPos<<std::endl;
            
            if(mSnakes.count(nPlayerPos) != 0)
            {
                std::cout<<"Dang, that's a snake bite! Go back at "<< mSnakes[nPlayerPos] << std::endl;
                nPlayerPos = mSnakes[nPlayerPos];
            }
            else if(mLadders.count(nPlayerPos) != 0)
            {
                std::cout<<"Woohooo, climb the ladder, move at "<< mLadders[nPlayerPos] << std::endl;
                nPlayerPos = mLadders[nPlayerPos];
            }

            nPlayersPosition[nCurrentPlayer] = nPlayerPos;
        }

        nCurrentPlayer = 1 - nCurrentPlayer;
        std::cout<<std::endl;
    }
    
    return 0;
}