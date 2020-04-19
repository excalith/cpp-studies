#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> values;
bool isGameRunning = true;
int moveCount = 0;
bool isPlayerTurn = true;

std::string playerMark = "\033[1;34mX\x1B[0m";
std::string enemyMark = "\033[1;31mO\x1B[0m";

void startGame();
void gameLoop();
void updateBoard();
void playerTurn();
void enemyTurn();

bool isMatch(int a, int b, int c)
{
    return (values[a] == values[b]) && (values[b] == values[c]);
}

bool isGameOver()
{
    if (isMatch(0, 1, 2))
    {
        // Row 1
        std::cout << "Game Over - " << values[0] << " wins" << std::endl;
        return true;
    }

    else if (isMatch(3, 4, 5))
    {
        // Row 2
        std::cout << "Game Over - " << values[3] << " wins" << std::endl;
        return true;
    }

    else if (isMatch(6, 7, 8))
    {
        // Row 3
        std::cout << "Game Over - " << values[6] << " wins" << std::endl;
        return true;
    }

    else if (isMatch(0, 4, 8))
    {
        // Diagonal
        std::cout << "Game Over - " << values[0] << " wins" << std::endl;
        return true;
    }

    else if (isMatch(2, 4, 6))
    {
        // Diagonal
        std::cout << "Game Over - " << values[2] << " wins" << std::endl;
        return true;
    }
    else if (moveCount >= 9)
    {
        // Draw
        std::cout << "Game Over - \033[1;33mDraw\x1B[0m" << std::endl;
        return true;
    }
    else
    {
        // Continue Game
        return false;
    }
}

int main()
{
    srand(time(0));
    while (isGameRunning)
    {
        startGame();
        gameLoop();

        std::string choice;
        std::cout << std::endl
                  << "Do you want to restart? [y/n]" << std::endl;
        std::cin >> choice;

        isGameRunning = choice == "y";
    }
}

void startGame()
{
    values = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};
    moveCount = 0;
    isPlayerTurn = true;
    updateBoard();
}


void gameLoop()
{
    while (isGameOver() == false)
    {
        if (isPlayerTurn)
            playerTurn();
        else
            enemyTurn();

        updateBoard();
    }
}

bool isValidMove(int choice)
{
    int choiceIndex = choice - 1;

    // Choice Index is out of grid bounds
    if ((choiceIndex < 0) || (choiceIndex > 8))
        return false;

    std::string choiceValue = values[choiceIndex];
    bool isValidMove = (choiceValue != playerMark) || (choiceValue != enemyMark);
    return isValidMove;
}

void playerTurn()
{
    // Get Player Input
    int choice;
    std::cout << "Your turn! Enter a number: ";
    std::cin >> choice;

    // Check Move Is Valid
    if (isValidMove(choice))
    {
        values[choice - 1] = playerMark;
        ++moveCount;
        isPlayerTurn = false;
    }
}

void enemyTurn()
{
    // Get All Available Slots
    std::vector<int> validList;
    for (int i = 0; i < 9; i++)
    {
        std::string value = values[i];
        if (value != playerMark && value != enemyMark)
        {
            validList.push_back(i);
        }
    }

    // Get A Random Slot
    if (validList.size() > 0)
    {
        int randomVal = rand() % validList.size();
        int valueVal = validList[randomVal];
        values[valueVal] = enemyMark;
        ++moveCount;
        std::cout << "Enemy played to " << randomVal + 1 << std::endl;
        isPlayerTurn = true;
    }
    else
    {
        // I Screwed Up Somewhere
        std::cout << "[ERROR] No Valid Slots Available!" << std::endl;
    }
}

void updateBoard()
{
    // Clear Terminal First
    system("clear");

    // Update Table With Values
    std::cout << "  \033[1;31mTic Tac Toe\x1B[0m" << std::endl;
    std::cout << "┌────┬────┬────┐" << std::endl;
    std::cout << "│ " << values[0] << "  │ " << values[1] << "  │ " << values[2] << "  │" << std::endl;
    std::cout << "├────┼────┼────┤" << std::endl;
    std::cout << "│ " << values[3] << "  │ " << values[4] << "  │ " << values[5] << "  │" << std::endl;
    std::cout << "├────┼────┼────┤" << std::endl;
    std::cout << "│ " << values[6] << "  │ " << values[7] << "  │ " << values[8] << "  │" << std::endl;
    std::cout << "└────┴────┴────┘" << std::endl;
    std::cout << std::endl;
}

