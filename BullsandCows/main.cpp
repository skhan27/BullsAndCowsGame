#include <iostream>
#include <string>
#include "FBullCowGame.h"

/*
FString, FText and int32 are used to specify what type of int in the unreal engine. This is prep for that

*/

using FText = std::string;
using int32 = int;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
FBullCowGame BCGame;
void PrintGameSummary();
int32 SelectWordLength();



int main() {
	
	bool WantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		WantsToPlayAgain = AskToPlayAgain();
	} while (WantsToPlayAgain);
	return 0;
}

void PlayGame()
{
	int32 WordLength = SelectWordLength();
	BCGame.SelectWord(WordLength);
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << "\nCows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);

	return Response[0] == 'Y' || Response [0] == 'y';
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congrats! You won! it took you " << BCGame.GetCurrentTry()-1 << " tries\n";
	}
	else {
		std::cout << "You lose! Better luck next time\n";
	}
}

int32 SelectWordLength()
{
	int32 WordLength = 0;
	while (WordLength != 3 && WordLength != 4 && WordLength != 6) {
		std::cout << "Please enter the length of the word you would like to guess (one of 3,4 or 6)\n";
		std::cin >> WordLength;
		std::cout << std::endl;
	}
	return WordLength;
}

void PrintIntro() {
	constexpr int32 WORD_LENGTH = 9;

	std::cout << "Welcome to the game\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I am thinking of\n";
	return;
}

FText GetValidGuess() {
	EWordStatus Status = EWordStatus::Invalid_Status;
	FText Guess = "";
	do {
		std::cout << "\nTry." << BCGame.GetCurrentTry() << " Enter Your Guess: ";
		
		// cin >> guess;  would work with one word but if theres a space the second word remains in the 
		// input stream and gets used in your next cin
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status) {
		case EWordStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EWordStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters\n";
			break;
		case EWordStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters\n";
			break;
		default:
			break;
		}
	} while (Status != EWordStatus::OK);
	return Guess;
}