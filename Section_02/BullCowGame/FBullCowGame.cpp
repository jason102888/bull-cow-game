#include "stdafx.h"
#include "FBullCowGame.h"
#include<stdio.h>
#include <map>
#define TMap std::map

// make syntax unreal friendly
using int32 = int;
using FString=std::string;


//constructors
FBullCowGame::FBullCowGame(){Reset();}
int32 FBullCowGame::GetMaxTries()const {
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5,10}, {6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry()const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength()const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{

	const FString HIDEN_WORD ="planet";
	MyHiddenWord = HIDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


bool FBullCowGame::IsGameWon()const{return bGameIsWon;}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) 
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EWordStatus::Upper_Case;
	}
	else if (Guess.length() !=GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	//recieves a VALID guess, incriments, and returns count
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length();//asuming same length as guess
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}

			}
		}
	}
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word)//for all letters of the word
	{
		Letter = tolower(Letter);//handle mixed case
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
}

