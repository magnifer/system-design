#include <iostream>
#include <map>
#include <random>
#include <vector>

class Dice
{
public:
    int RollDice()
    {
        static std::random_device rd;                     // Non-deterministic seed
        static std::mt19937 gen(rd());                    // Mersenne Twister engine
        static std::uniform_int_distribution<> dis(1, 6); // Range [1, 6]
        return dis(gen);
    }
};

class Player
{
public:
    Player(std::string szName) : nPosition(0), szPlayerName(szName) {}
    Player(Player &player) = delete;
    Player(Player &&player)
    {
        std::cout << "Move constructor invoked";
    };

    int GetPosition() const { return nPosition; };
    void SetPosition(const int nPos) { nPosition = nPos; };
    std::string GetName() { return szPlayerName; };

private:
    int nPosition;
    std::string szPlayerName;
};

class Board
{
public:
    Board()
    {
        mSnakes = {{99, 10}, {92, 55}, {77, 32}, {44, 25}, {24, 3}};
        mLadders = {{3, 24}, {21, 43}, {47, 87}, {75, 95}};
    }

    int GetNewPosition(int nPosition)
    {
        if (mSnakes.count(nPosition))
        {
            std::cout << "Dang, that's a snake bite! Go back at " << mSnakes[nPosition] << std::endl;
            return mSnakes[nPosition];
        }
        else if (mLadders.count(nPosition))
        {
            std::cout << "Woohooo, climb the ladder, move at " << mLadders[nPosition] << std::endl;
            return mLadders[nPosition];
        }
        return nPosition;
    }

private:
    std::map<int, int> mSnakes;
    std::map<int, int> mLadders;
};

class Game
{
public:
    Game()
    {
        vPlayers.emplace_back("Player_1");
        vPlayers.emplace_back("Player_2");
    }

    void PlayGame()
    {
        while (true)
        {
            std::cout << "  === Round " << ++nRound << " begin's. ===\n";
            std::cin.get();

            Player &currentPlayer = vPlayers[nCurrentPlayerIndex];
            std::cout << "=== Player" << currentPlayer.GetName() << "'s turn ===\n";

            std::cout << "=== Press ENTER to roll DICE === \n";

            int nRandOutcome = dice.RollDice();
            std::cout << "=== Dice roll outcome is : " << nRandOutcome << "=== \n";

            int nNewPos = currentPlayer.GetPosition() + nRandOutcome;

            if (nNewPos == 100)
            {
                std::cout << "==== Player" << currentPlayer.GetName() << " reached at 100 !!! Congratulations you WON ==== \n";
                break;
            }
            else if (nNewPos > 100)
            {
                std::cout << "Player" << currentPlayer.GetName() << " can't move! wait for next round";
            }
            else
            {
                std::cout << currentPlayer.GetName() << " moves to " << nNewPos << "\n";
                nNewPos = board.GetNewPosition(nNewPos);
                currentPlayer.SetPosition(nNewPos);
            }

            nCurrentPlayerIndex = 1 - nCurrentPlayerIndex; // switch players
            std::cout << "\n";
        }
    }

private:
    Dice dice;
    Board board;
    std::vector<Player> vPlayers;
    int nCurrentPlayerIndex = 0;
    int nRound = 0;
};

int main()
{
    Game game;
    game.PlayGame();

    return 0;
}
