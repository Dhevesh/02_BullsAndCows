#include "FBullCow.h"
#include <string>
using FText = std::string;
FBullCowGame BCGame = FBullCowGame();

FText GetValidGuess();
void PrintIntro();
void PlayGame();
void PrintSummary();
bool PlayAgain();

int main()
{
	do {
		BCGame.GetWordLength();
		BCGame.Reset();
		PrintIntro();
		PlayGame();
		PrintSummary();
	} while (PlayAgain() == true);
	return 0;
}

void PlayGame()
{
	do {
		FText Guess = GetValidGuess();
		BCGame.SubmitGuess(Guess);
	} while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && !BCGame.isGameWon());
}

bool PlayAgain()
{
	FString Answer = "";
	std::cout << "Do you want to Play Again?(y/n): "; // TODO future make a few hidden words of varying lengths that player can choose from.
	std::getline(std::cin, Answer);
	std::cout << std::endl;
	return (Answer[0] == 'y') || (Answer[0] == 'Y');
}


FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Guess;
	FText Guess = "";
	do
	{
		
		std::cout << "Enter your Guess(" << BCGame.GetCurrentTry() << "/" << BCGame.GetMaxTries() << "): ";
		std::getline(std::cin, Guess);
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::OK:
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please ensure your word has no repeat letters.\n\n";
			break;
		case EGuessStatus::Invalid_Length:
			std::cout << "Please enter a " << BCGame.HiddenWordLength << " letter word.\n\n";
			break;
		case EGuessStatus::Not_Lower_Case:
			std::cout << "Please enter only lowercase letters.\n\n";
			break;
		default:
			return Guess;
		}

	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PrintIntro()
{
	std::cout << "Welcome to the Bulls and Cows Game.\n";
	std::cout << "An Isogram is a word that contains no repeat letters.\n\n";
	std::cout << "Can you guess the " << BCGame.HiddenWordLength << " letter word that I am thinking off?\n";
}

void PrintSummary()
{
	if (BCGame.isGameWon() == true) {
		std::cout << "Congratulations! You Guessed the Correct Word!\n";
	}
	else {
		std::cout << "Better Luck Next Time!\n";
	}
}




