#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include"MyLib.h";

using namespace std;

/*
 * Enum: enChoice
 * Represents the available choices in the game: Rock, Paper, or Scissors.
 */
enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };

/*
 * Enum: enWinner
 * Represents the possible outcomes of a round: Draw, Player wins, or Computer wins.
 */
enum enWinner { Draw, Player, Computer };

/*
 * Struct: stGameStats
 * Holds statistics of the entire game session.
 */
struct stGameStats {
    short gameRounds = 0;       // Total number of rounds played
    short playerWonTimes = 0;   // Number of times the player has won
    short computerWonTimes = 0; // Number of times the computer has won
    short drawTimes = 0;        // Number of draws
};

/*
 * Function: randomNum
 * Generates a random number between 'from' and 'to' inclusive.
 */
short randomNum(short from, short to) {
    return rand() % (to - from + 1) + from;
}

/*
 * Function: numOfRounds
 * Prompts the user to enter the number of rounds and validates the input.
 */
short numOfRounds(stGameStats& stats) {
    cout << "How many rounds ? ";
    cin >> stats.gameRounds;
    while (cin.fail())
    {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid number, Enter a valid one : ";
        cin >> stats.gameRounds;
    }
    return stats.gameRounds;
}

/*
 * Function: playerChoice
 * Prompts the player to select Rock, Paper, or Scissors and validates input.
 */
enChoice playerChoice() {
    short choice;
    cout << "Your choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 3) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Invalid choice, Enter 1, 2, or 3 : ";
        cin >> choice;
    }
    return static_cast<enChoice>(choice);
}

/*
 * Function: computerChoice
 * Randomly generates the computer's choice.
 */
enChoice computerChoice() {
    return static_cast<enChoice>(randomNum(enChoice::Rock, enChoice::Scissors));
}

/*
 * Function: theWinner
 * Determines the winner of a round based on player and computer choices.
 */
enWinner theWinner(enChoice player, enChoice computer) {
    if (player == computer) return enWinner::Draw;
    if ((player == enChoice::Rock && computer == enChoice::Scissors) ||
        (player == enChoice::Paper && computer == enChoice::Rock) ||
        (player == enChoice::Scissors && computer == enChoice::Paper))
        return enWinner::Player;
    return enWinner::Computer;
}

/*
 * Function: returnChoice
 * Converts a choice (Rock, Paper, Scissors) to its string representation.
 */
string returnChoice(enChoice choice) {
    switch (choice)
    {
    case enChoice::Rock:     return "Rock";
    case enChoice::Paper:    return "Paper";
    case enChoice::Scissors: return "Scissors";
    default: return "Unknown";
    }
}

/*
 * Function: returnWinner
 * Converts the winner enum to a string representation.
 */
string returnWinner(enWinner winner) {
    switch (winner)
    {
    case enWinner::Draw:     return "Draw";
    case enWinner::Player:   return "Player";
    case enWinner::Computer: return "Computer";
    default: return "Unknown";
    }
}

/*
 * Function: printRoundScreen
 * Displays the round summary including both choices and the round winner.
 */
void printRoundScreen(short round, enChoice player, enChoice computer) {
    cout << "______________________Round[" << round << "]______________________\n\n";
    cout << "Player choice  : " << returnChoice(player) << "\n";
    cout << "Computer choice: " << returnChoice(computer) << "\n";
    cout << "Round winner   : [" << returnWinner(theWinner(player, computer)) << "]\n";
    cout << "\n____________________________________________________\n" << endl;
}

/*
 * Function: roundScreen
 * Handles a single round: gets choices, determines winner, updates stats,
 * and changes console color based on the outcome.
 */
void roundScreen(short round, stGameStats& stats) {
    cout << "\nRound [" << round << "] begins:\n\n";
    enChoice player = playerChoice();
    enChoice computer = computerChoice();
    printRoundScreen(round, player, computer);

    switch (theWinner(player, computer))
    {
    case enWinner::Draw: {
        stats.drawTimes++;
        system("color 6F"); // Yellow for a draw
        break;
    }

    case enWinner::Player: {
        stats.playerWonTimes++;
        system("color 2F"); // Green for player win
        break;
    }

    case enWinner::Computer: {
        stats.computerWonTimes++;
        system("color 4F"); // Red for computer win
        cout << "\a";       // Beep sound on loss
        break;
    }
    }
}

/*
 * Function: printRoundsScreen
 * Plays multiple rounds based on the number of rounds entered by the user.
 */
void printRoundsScreen(stGameStats& stats) {
    short rounds = numOfRounds(stats);
    for (int i = 1; i <= rounds; i++)
    {
        roundScreen(i, stats);
    }
    cout << "Press any button to move to Final Results Screen...";
    system("pause>0");
}

/*
 * Function: printFinalResults
 * Displays the overall game results after all rounds are completed.
 */
void printFinalResults(stGameStats& stats) {
    system("cls");
    system("color 07");
    MyLib::printCentered("_____________________________________________________________________"); cout << "\n\n";
    MyLib::printCentered("+++ G a m e   O v e r +++"); cout << "\n";
    MyLib::printCentered("_____________________________________________________________________"); cout << "\n\n";
    MyLib::printCentered("____________________________[Game Results]___________________________"); cout << "\n\n";
    MyLib::printCentered("Game rounds        : "); cout << stats.gameRounds << "\n";
    MyLib::printCentered("Player won times   : "); cout << stats.playerWonTimes << "\n";
    MyLib::printCentered("Computer won times : "); cout << stats.computerWonTimes << "\n";
    MyLib::printCentered("Draw times         : "); cout << stats.drawTimes << "\n";
    MyLib::printCentered("Final winner       : ");
    (stats.playerWonTimes == stats.computerWonTimes) ? cout << "No Winner\n\n" :
        (stats.playerWonTimes > stats.computerWonTimes) ? cout << "Player\n\n" : cout << "Computer\n\n";
    MyLib::printCentered("_____________________________________________________________________"); cout << "\n" << endl;
}

/*
 * Function: RockPaperScissorsGame
 * Main game loop: initializes stats, runs rounds, shows results,
 * and handles replay functionality.
 */
void RockPaperScissorsGame() {
    srand((unsigned)time(NULL)); // Seed random number generator
    stGameStats stats;
    char playAgain;
    do {
        stats = {}; // Reset stats for a new game
        printRoundsScreen(stats);
        printFinalResults(stats);
        cout << "\n\nDo you want to play again? Y/N? ";
        cin >> playAgain;
        while (toupper(playAgain) != 'Y' && toupper(playAgain) != 'N') {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "Invalid input, please enter Y or N: ";
            cin >> playAgain;
        }
        system("cls");
        system("color 07");
    } while (toupper(playAgain) == 'Y');
}

/*
 * Function: main
 * Entry point of the program. Starts the Rock-Paper-Scissors game.
 */
int main() {
    RockPaperScissorsGame();
}
