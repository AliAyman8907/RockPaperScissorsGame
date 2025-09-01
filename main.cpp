#include<iostream>
#include<string>
#include<cstdlib>

using namespace std;

short gameRounds = 0, playerWonTimes = 0, computerWonTimes = 0, drawTimes = 0;

enum enChoice { Rock = 1, Paper = 2, Scissors = 3 };

enum enWinner { Draw, Player, Computer };

short randomNum(short from, short to) {
	return rand() % (to - from + 1) + from;
}

short numOfRounds() {
	do
	{
		cout << "How many rounds (1 to 10) ? ";
		cin >> gameRounds;
	} while (gameRounds < 1 || gameRounds > 10);
	return gameRounds;
}

enChoice playerChoice() {
	short choice;
	cout << "Your choice: [1]:Rock, [2]:Paper, [3]:Scissors ? ";
	cin >> choice;
	switch (choice)
	{
	case 1: return enChoice::Rock;
	case 2: return enChoice::Paper;
	case 3: return enChoice::Scissors;
	}
}

enChoice computerChoice() {
	switch (randomNum(enChoice::Rock, enChoice::Scissors))
	{
	case 1: return enChoice::Rock;
	case 2: return enChoice::Paper;
	case 3: return enChoice::Scissors;
	}
}

enWinner theWinner(enChoice player, enChoice computer) {
	if (player == computer) return enWinner::Draw;
	else if (player == enChoice::Rock && computer == enChoice::Paper)      return enWinner::Computer;
	else if (player == enChoice::Rock && computer == enChoice::Scissors)   return enWinner::Player;
	else if (player == enChoice::Paper && computer == enChoice::Rock)      return enWinner::Player;
	else if (player == enChoice::Paper && computer == enChoice::Scissors)  return enWinner::Computer;
	else if (player == enChoice::Scissors && computer == enChoice::Rock)   return enWinner::Computer;
	else/*(player == enChoice::Scissors && computer == enThePlay::Paper)*/ { return enWinner::Player; }
}

string returnChoice(enChoice choice) {
	switch (choice)
	{
	case enChoice::Rock:     return "Rock";
	case enChoice::Paper:    return "Paper";
	case enChoice::Scissors: return "Scissors";
	}
}

string returnWinner(enWinner winner) {
	switch (winner)
	{
	case enWinner::Draw:     return "Draw";
	case enWinner::Player:   return "Player";
	case enWinner::Computer: return "Computer";
	}
}

void printRoundScreen(short round, enChoice player, enChoice computer) {
	cout << "______________________Round[" << round << "]______________________\n\n";
	cout << "Player choice  : " << returnChoice(player) << "\n";
	cout << "Computer choice: " << returnChoice(computer) << "\n";
	cout << "Round winner   : [" << returnWinner(theWinner(player, computer)) << "]\n";
	cout << "\n____________________________________________________\n" << endl;
}

void roundScreen(short round) {
	cout << "\nRound [" << round << "] begins:\n\n";
	enChoice player = playerChoice();
	enChoice computer = computerChoice();
	printRoundScreen(round, player, computer);
	switch (theWinner(player, computer))
	{
	case enWinner::Draw: {
		drawTimes++;
		system("color 6F");
		break;
	}

	case enWinner::Player: {
		playerWonTimes++;
		system("color 2F");
		break;
	}

	case enWinner::Computer: {
		computerWonTimes++;
		system("color 4F");
		cout << "\a";
		break;
	}
	}
}

void printRoundsScreen() {
	short rounds = numOfRounds();
	for (int i = 1; i <= rounds; i++)
	{
		roundScreen(i);

	}
}

void printFinalResults() {
	cout << "\t\t\t\t_____________________________________________________________________\n\n";
	cout << "\t\t\t\t                      +++ G a m e   O v e r +++\n\n";
	cout << "\t\t\t\t_____________________________________________________________________\n\n";
	cout << "\t\t\t\t____________________________[Game Results]___________________________\n\n";
	cout << "\t\t\t\tGame rounds        : " << gameRounds << "\n";
	cout << "\t\t\t\tPlayer won times   : " << playerWonTimes << "\n";
	cout << "\t\t\t\tComputer won times : " << computerWonTimes << "\n";
	cout << "\t\t\t\tDraw times         : " << drawTimes << "\n";
	cout << "\t\t\t\tFinal winner       : ";
	(playerWonTimes == computerWonTimes) ? cout << "No Winner\n" :
		(playerWonTimes > computerWonTimes) ? cout << "Player\n" : cout << "Computer\n";
	cout << "\n\t\t\t\t_____________________________________________________________________\n" << endl;
}

void RockPaperScissorsGame() {
	srand((unsigned)time(NULL));
	char playAgain;
	printRoundsScreen();
	printFinalResults();
	cout << "Do you want to play again? Y/N? ";
	cin >> playAgain;
	if (toupper(playAgain) == 'Y') {
		system("cls");
		system("color 07");
		RockPaperScissorsGame();
	}
}

int main() {
	RockPaperScissorsGame();
}