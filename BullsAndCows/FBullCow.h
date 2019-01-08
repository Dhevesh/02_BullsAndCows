#pragma once
#include <string>
#include <iostream>
using int32 = int;
using FString = std::string;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Guess,
	OK,
	Not_Isogram,
	Invalid_Length,
	Not_Lower_Case
};

class FBullCowGame
{
public:
	int32 GetCurrentTry();
	int32 GetMaxTries() const;
	void GetWordLength();
	FString GetHiddenWord() const;
	FString SubmitGuess(FString);
	bool isGameWon() const;
	FBullCowGame();
	void Reset();
	EGuessStatus CheckGuessValidity(FString Guess) const;

	int32 HiddenWordLength;

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};


