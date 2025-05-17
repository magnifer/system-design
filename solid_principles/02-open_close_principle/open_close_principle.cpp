#include <iostream>
#include <map>
#include <random>
#include <vector>

/* DICE LOGIC */
class IDice
{
public:
    virtual ~IDice() {};
    virtual int RollDice() = 0;
};

class StandardDice : public IDice
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
class BiasedDice : public IDice
{
    // maybe Favoiring certain no
};
class LoadedDice : public IDice
{
    // Maybe More 6's
};

/* PLAYER LOGIC */
class Player
{
public:
    Player(std::string szName) : nPosition(0), szPlayerName(szName)
    {
        std::cout << "Parameterized constructor invoked\n";
    }
    Player(Player &player) noexcept
        : nPosition(player.nPosition),
          szPlayerName(player.szPlayerName)
    {
        std::cout << "Copy Constructor invoked\n";
    }
    Player(Player &&player) noexcept
        : nPosition(player.nPosition),
          szPlayerName(std::move(player.szPlayerName))
    {
        std::cout << "Move constructor invoked\n";
    };

    int GetPosition() const { return nPosition; };
    void SetPosition(const int nPos) { nPosition = nPos; };
    std::string GetName() { return szPlayerName; };

private:
    int nPosition;
    std::string szPlayerName;
};

/* BOARD LOGIC */
class IBoardRule
{
public:
    virtual ~IBoardRule() {};
    virtual bool AppliesTo(int nPosition) = 0;
    virtual int GetNewPosition(int nPosition) = 0;
};

class SnakeRule : public IBoardRule
{
public:
    SnakeRule(std::map<int, int> mSnakes) : m_mSnakes(mSnakes) {}

    bool AppliesTo(int nPosition) override
    {
        return m_mSnakes.count(nPosition);
    }
    int GetNewPosition(int nPosition) override
    {
        std::cout << "Dang, that's a snake bite! Go back at " << m_mSnakes[nPosition] << std::endl;
        return m_mSnakes.at(nPosition);
    }

private:
    std::map<int, int> m_mSnakes;
};

class LadderRule : public IBoardRule
{
public:
    LadderRule(std::map<int, int> mLadders) : m_mLadders(mLadders) {}

    bool AppliesTo(int nPosition) override
    {
        return m_mLadders.count(nPosition);
    }
    int GetNewPosition(int nPosition) override
    {
        std::cout << "Woohooo, climb the ladder, move at " << m_mLadders[nPosition] << std::endl;
        return m_mLadders.at(nPosition);
    }

private:
    std::map<int, int> m_mLadders;
};

class Board
{
public:
    void AddRule(IBoardRule *rule)
    {
        vBoardRules.push_back(rule);
    }
    int GetNewPosition(int nPosition)
    {
        for (auto rule : vBoardRules)
        {
            if (rule->AppliesTo(nPosition))
            {
                return rule->GetNewPosition(nPosition);
            }
        }
        return nPosition;
    }

private:
    std::vector<IBoardRule *> vBoardRules;
};

class Game
{
public:
    Game(IDice *dice) : m_pDice(dice)
    {
        m_vPlayers.emplace_back("Player_1");
        m_vPlayers.emplace_back("Player_2");

        m_Board.AddRule(new SnakeRule({{99, 10}, {92, 55}, {77, 32}, {44, 25}, {24, 3}}));
        m_Board.AddRule(new LadderRule({{3, 24}, {21, 43}, {47, 87}, {75, 95}}));
    }

    void PlayGame()
    {
        while (true)
        {
            std::cout << "  === Round " << ++nRound << " begin's. ===\n";
            std::cin.get();

            Player &currentPlayer = m_vPlayers[nCurrentPlayerIndex];
            std::cout << "=== " << currentPlayer.GetName() << "'s turn ===\n";
            std::cout << "=== Press ENTER to roll DICE === \n";

            int nRandOutcome = m_pDice->RollDice();
            std::cout << "=== Dice roll outcome is : " << nRandOutcome << "=== \n";

            int nNewPos = currentPlayer.GetPosition() + nRandOutcome;
            if (nNewPos == 100)
            {
                std::cout << "==== " << currentPlayer.GetName() << " reached at 100 !!! Congratulations you WON ==== \n";
                break;
            }
            else if (nNewPos > 100)
            {
                std::cout << "=== " << currentPlayer.GetName() << " can't move! wait for next round ===";
            }
            else
            {
                std::cout << currentPlayer.GetName() << " moves to " << nNewPos << "\n";
                nNewPos = m_Board.GetNewPosition(nNewPos);
                currentPlayer.SetPosition(nNewPos);
            }

            nCurrentPlayerIndex = 1 - nCurrentPlayerIndex; // switch players
            std::cout << "\n";
        }
    }

private:
    IDice *m_pDice;
    Board m_Board;
    std::vector<Player> m_vPlayers;
    int nCurrentPlayerIndex = 0;
    int nRound = 0;
};

int main()
{
    IDice *dice = new StandardDice();
    Game game(dice);
    game.PlayGame();

    delete dice;

    return 0;
}
