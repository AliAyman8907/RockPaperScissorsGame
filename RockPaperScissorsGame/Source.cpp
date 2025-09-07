#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include"MyLib.h";

using namespace std;

enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };

enum enWinner { Draw, Player, Computer };

struct GameStats {
	short gameRounds = 0;
	short playerWonTimes = 0;
	short computerWonTimes = 0;
	short drawTimes = 0;
};

short randomNum(short from, short to) {
	return rand() % (to - from + 1) + from;
}

short numOfRounds(GameStats& stats) {
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

enChoice computerChoice() {
	return static_cast<enChoice>(randomNum(enChoice::Rock, enChoice::Scissors));
}

enWinner theWinner(enChoice player, enChoice computer) {
	if (player == computer) return enWinner::Draw;
	if ((player == enChoice::Rock && computer == enChoice::Scissors) ||
		(player == enChoice::Paper && computer == enChoice::Rock) ||
		(player == enChoice::Scissors && computer == enChoice::Paper))
		return enWinner::Player;
	return enWinner::Computer;
}

string returnChoice(enChoice choice) {
	switch (choice)
	{
	case enChoice::Rock:     return "Rock";
	case enChoice::Paper:    return "Paper";
	case enChoice::Scissors: return "Scissors";
	default: return "Unknown";
	}
}

string returnWinner(enWinner winner) {
	switch (winner)
	{
	case enWinner::Draw:     return "Draw";
	case enWinner::Player:   return "Player";
	case enWinner::Computer: return "Computer";
	default: return "Unknown";
	}
}

void printRoundScreen(short round, enChoice player, enChoice computer) {
	cout << "______________________Round[" << round << "]______________________\n\n";
	cout << "Player choice  : " << returnChoice(player) << "\n";
	cout << "Computer choice: " << returnChoice(computer) << "\n";
	cout << "Round winner   : [" << returnWinner(theWinner(player, computer)) << "]\n";
	cout << "\n____________________________________________________\n" << endl;
}

void roundScreen(short round, GameStats& stats) {
	cout << "\nRound [" << round << "] begins:\n\n";
	enChoice player = playerChoice();
	enChoice computer = computerChoice();
	printRoundScreen(round, player, computer);
	switch (theWinner(player, computer))
	{
	case enWinner::Draw: {
		stats.drawTimes++;
		system("color 6F");
		break;
	}

	case enWinner::Player: {
		stats.playerWonTimes++;
		system("color 2F");
		break;
	}

	case enWinner::Computer: {
		stats.computerWonTimes++;
		system("color 4F");
		cout << "\a";
		break;
	}
	}
}

void printRoundsScreen(GameStats& stats) {
	short rounds = numOfRounds(stats);
	for (int i = 1; i <= rounds; i++)
	{
		roundScreen(i, stats);

	}
	cout << "Press any button to move to Final Results Screen...";
	system("pause>0");
}

void printFinalResults(GameStats& stats) {
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

void RockPaperScissorsGame() {
	srand((unsigned)time(NULL));
	GameStats stats;
	char playAgain;
	do {
		stats = {};
		printRoundsScreen(stats);
		printFinalResults(stats);
		cout << "Do you want to play again? Y/N? ";
		cin >> playAgain;
		system("cls");
		system("color 07");
	} while (toupper(playAgain) == 'Y');
}

int main() {
	RockPaperScissorsGame();
}