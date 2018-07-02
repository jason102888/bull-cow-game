//the game logic (no view code or direct user interaction, simple guess the word game based on Mastermind
#pragma once
#include<iostream>
#include<string>
#include "stdafx.h"

//make unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Upper_Case,
	Wrong_Length,
};

class FBullCowGame 

{
public:
	FBullCowGame();//constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry()const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon()const;

	void Reset(); //make a return value
	EWordStatus CheckGuessValidity(FString) const;
	FBullCowCount SubmitValidGuess(FString);
private:
	//see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool IsIsogram(FString) const;
	bool bGameIsWon;
	bool IsLowercase(FString) const;
};