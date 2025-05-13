#include <iostream>
#include <map>
#include <random>
#include <vector>

class Dice {
public:
    int Roll() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        static std::uniform_int_distribution<> dis(1, 6);
        return dis(gen);
    }
};

class Board {
private:
    std::map<int, int> snakes;
    std::map<int, int> ladders;

public:
    Board() {
        snakes = {{99, 10}, {92, 55}, {77, 32}, {44, 25}, {25, 3}};
        ladders = {{3, 24}, {21, 43}, {47, 87}, {75, 95}};
    }

    int GetNewPosition(int position) {
        if (snakes.count(position)) {
            std::cout << "Dang, snake bite! Go back to " << snakes[position] << "\n";
            return snakes[position];
        }
        if (ladders.count(position)) {
            std::cout << "Climb the ladder to " << ladders[position] << "\n";
            return ladders[position];
        }
        return position;
    }
};

class Player {
private:
    int position;
    std::string name;

public:
    Player(std::string name) : position(0), name(name) {}

    int GetPosition() const { return position; }
    void SetPosition(int pos) { position = pos; }
    std::string GetName() const { return name; }
};

class Game {
private:
    Dice dice;
    Board board;
    std::vector<Player> players;
    int currentPlayerIndex = 0;
    int round = 0;

public:
    Game() {
        players.emplace_back("Player 0");
        players.emplace_back("Player 1");
    }

    void Play() {
        std::cout << "=== Snake and Ladder Game ===\n";
        while (true) {
            std::cout << "=== Round " << ++round << " === Press ENTER to play...\n";
            std::cin.get();

            Player& currentPlayer = players[currentPlayerIndex];
            std::cout << currentPlayer.GetName() << "'s turn\n";

            int roll = dice.Roll();
            std::cout << "Rolled: " << roll << "\n";

            int newPos = currentPlayer.GetPosition() + roll;
            if (newPos == 100) {
                std::cout << currentPlayer.GetName() << " reached 100 and won the game!\n";
                break;
            } else if (newPos > 100) {
                std::cout << currentPlayer.GetName() << " can't move. Wait for next round.\n";
            } else {
                std::cout << currentPlayer.GetName() << " moves to " << newPos << "\n";
                newPos = board.GetNewPosition(newPos);
                currentPlayer.SetPosition(newPos);
            }

            currentPlayerIndex = 1 - currentPlayerIndex; // switch players
            std::cout << "\n";
        }
    }
};

int main() {
    Game game;
    game.Play();
    return 0;
}
