#include "FBullCow.h"
#include <map>
#define TMap std::map

int32 FBullCowGame::GetCurrentTry() { return MyCurrentTry; }
bool FBullCowGame::isGameWon() const { return bIsGameWon; }

FBullCowGame::FBullCowGame() { Reset(); } //default constructor

FString FBullCowGame::GetHiddenWord() const { 
	TMap<int32, FString> HiddenWord{
	{3,"ant"},
	{6,"planet"},
	{8,"absolute"},
	{10,"fishmonger"}
	};
	return HiddenWord[HiddenWordLength]; 
}

void FBullCowGame::GetWordLength() { 
	FString PlayerChoice = "";
	TMap<char, int32> Difficulty{ {'e', 3}, { 'm',6 }, { 'h',8 }, { 'v',10 }}; //easy, medium, hard, very hard
	bool bIsValidChoice = false;
	do {
	std::cout << "Please select a difficulty [E]asy, [M]edium, [H]ard, [V]ery Hard : ";
	getline(std::cin, PlayerChoice);
	
		switch (tolower(PlayerChoice[0])) {
		case 'e':
			bIsValidChoice = true;
			break;
		case 'm':
			bIsValidChoice = true;
			break;
		case 'h':
			bIsValidChoice = true;
			break;
		case 'v':
			bIsValidChoice = true;
			break;
		default:
			bIsValidChoice = false;
			std::cout << "Please enter a valid choice!\n\n";
			break;
			
		}

	} while (bIsValidChoice == false);
	HiddenWordLength = Difficulty[tolower(PlayerChoice[0])];
}

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3,5},{4,7},{5,10},{6,15},{7,20},{8,20},{9,23},{10,25} };
	return WordLengthToMaxTries[HiddenWordLength]; 
}

FString FBullCowGame::SubmitGuess(FString Guess)
{
	FBullCowCount BullCowCount;
	FString Hint = "";
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
					Hint += Guess[i];
				}
				else
				{
					BullCowCount.Cows++;
					Hint += Guess[i];
				}
			}
		}
	}
	std::cout << "Bulls: " << BullCowCount.Bulls << " Cows: " << BullCowCount.Cows;
	std::cout << std::endl;
	std::cout << "Correct Letters: " << Hint << "\n\n";
	if (BullCowCount.Bulls == HiddenWordLength) {
		bIsGameWon = true;
	}
	MyCurrentTry++;
	return Guess;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lower_Case;
	}
	else if (Guess.length() != HiddenWordLength)
	{
		return EGuessStatus::Invalid_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}

}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	if (Guess.length() <= 1) { return true; }

	TMap<char, bool> LetterSeen;
	for (auto& Letter : Guess) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) {
			return false;
		}
		else{ 
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const
{
	for (auto& Letter : Guess) {
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}

void FBullCowGame::Reset()
{
	bIsGameWon = false;
	constexpr int32 CurrentTry = 1;
	MyCurrentTry = CurrentTry;
	MyHiddenWord = GetHiddenWord(); // TODO replace with word library
	return;
}








