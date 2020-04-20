#include <iostream>
#include <vector>

std::vector<std::string> wordList = {
    "megahertz",
    "mnemonic",
    "pneumonia",
    "witchcraft",
    "jiujitsu",
    "disavow",
    "void",
    "gazebo",
    "zipper",
    "rhythm",
    "pep talk",
    "easter egg",
    "black friday",
    "piece of cake",
    "sense of humour",
    "so say we all",
    "light years away",
    "kick the bucket",
    "raining cats and dogs",
    "down with the sickness"};
std::string targetWord;
std::vector<char> hiddenChars;
std::string discardedChars;
bool isGameRunning = true;
int failCount;
int successCount;

/** Checks Game Over By Win Or Fail */
bool isGameOver()
{
    std::string choice;

    // Check Game Status
    bool isSuccess = successCount + 1 >= targetWord.size();
    bool isFailed = failCount >= 7;
    if (isSuccess || isFailed)
    {
        if (isSuccess)
        {
            std::cout << std::endl
                      << "Game Over, You Win!" << std::endl;
            std::cout << std::endl
                      << "Do you want to continue? [y/n]" << std::endl;
        }
        else
        {
            std::cout << std::endl
                      << "Game Over, You Lost!" << std::endl;
            std::cout << "The Word Was: " << targetWord << std::endl;
            std::cout << std::endl
                      << "Do you want to retry? [y/n]" << std::endl;
        }

        std::cin >> choice;
        isGameRunning = choice == "y";
        return true;
    }

    // Keep Game On
    return false;
}

void startGame();
void getRandomWord();
void getUserInput();
void gameLoop();
void updateDisplay();

/** Main Loop */
int main()
{
    srand(time(0));

    while (isGameRunning)
    {
        startGame();
        gameLoop();
    }
}

/** Resets And Initializes Game */
void startGame()
{
    // Reset All Data
    targetWord.clear();
    hiddenChars.clear();
    discardedChars.clear();
    successCount = 0;
    failCount = 0;

    // Initialize Game
    getRandomWord();
    updateDisplay();
}

/** Runs Game Loop */
void gameLoop()
{
    while (isGameOver() == false)
    {
        getUserInput();
        updateDisplay();
    }
}

/** Get User Input For Chars */
void getUserInput()
{
    // Get User Input
    char choice;
    std::cout << std::endl
              << "Guess a character" << std::endl;
    std::cin >> choice;

    // IF Char Already Discarded Return To Main Loop
    bool isDiscarded = false;
    for (int i = 0; i < discardedChars.size(); i++)
    {
        char c = discardedChars[i];
        if (c == choice)
            return;
    }

    // Does Char Match With Target Word
    bool isMatch = false;
    for (int i = 0; i < targetWord.size(); i++)
    {
        char c = targetWord[i];
        if (c == choice)
        {
            // Is Char Already Found Return To Main Loop
            if (hiddenChars[i] == choice)
                return;

            hiddenChars[i] = choice;

            // Increment Success Count
            ++successCount;
            isMatch = true;
        }
    }

    // If Char Does Not Match, Increment Fail Count
    if (isMatch == false)
    {
        ++failCount;
        bool hasChar = discardedChars.find(choice) == true;
        if (hasChar == false)
            discardedChars.push_back(choice);
    }
}

/** Gets A Random Word From WordList */
void getRandomWord()
{
    // Get A Random Word
    int randomVal = rand() % wordList.size();
    targetWord = wordList[randomVal];

    // Setup Hidden Chars
    for (int i = 0; i < targetWord.size(); i++)
    {
        char c = targetWord[i];
        char newChar = isspace(c) ? ' ' : '_';
        hiddenChars.push_back(newChar);
    }
}

/** Updates Hangman Display */
void updateDisplay()
{
    system("clear");

    // Get Conditional Hangman Body Pieces
    std::string rope = failCount > 0 ? "╒" : "═";
    std::string head = failCount > 1 ? "@" : " ";
    std::string body = failCount > 2 ? "|" : " ";
    std::string rArm = failCount > 3 ? "/" : " ";
    std::string lArm = failCount > 4 ? "\\" : " ";
    std::string rLeg = failCount > 5 ? "/" : " ";
    std::string lLeg = failCount > 6 ? "\\" : " ";

    // Display Hangman
    std::cout << "      " << rope << "═════╗" << std::endl;
    std::cout << "      " << head << "     ║" << std::endl;
    std::cout << "     " << rArm << body << lArm << "    ║" << std::endl;
    std::cout << "     " << rLeg << " " << lLeg << "    ║" << std::endl;
    std::cout << "            ║" << std::endl;
    std::cout << "   ═════════╝" << std::endl;
    std::cout << std::endl;

    // Show Target Word
    std::string s(hiddenChars.begin(), hiddenChars.end());
    std::cout << "   " << s << std::endl;
    std::cout << std::endl;

    // Show Progression Data
    std::cout << "Discarded: " << discardedChars << std::endl;
    std::cout << "Life Left: " << 7 - failCount << std::endl;
}
