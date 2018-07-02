/*This is the cconsole executable, that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for 
all	user interaction. For game logic see the FBullCowGame class.*/

#include <iostream>
#include <string>
#include "stdafx.h"
#include"FBullCowGame.h"

//make unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame; //instantiate a new game, which we re-use across plays

//the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);
	return 0;//exit the aplication
}

//introduce the game
void PrintIntro()
{
	
	std::cout << "\n\nwelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}
//plays single game to completion
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	std::cout << MaxTries<<std::endl;
	//loop for the number of turns asking for guesses
	
	constexpr int32 NUMBER_OF_TURNS = 5;
	while(!BCGame.IsGameWon()&& BCGame.GetCurrentTry()<=MaxTries)
	{
		FText Guess = GetValidGuess();
		
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		//print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";

		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
	
}

//loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid_Status;
	do
	{
		//get a guess from the player
		int CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << " enter your guess: ";
		std::getline(std::cin, Guess);

		 Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Not_Isogram:
			std::cout << "please enter a Isogram.\n";
			break;
		case EWordStatus::Upper_Case:
			std::cout << "please enter a lower case answer";
			break;
		case EWordStatus::Wrong_Length:
			std::cout << "please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		default:
			//assume the guess is valid
			break;
		}
		std::cout << std::endl;
	}
	while (Status!=EWordStatus::OK);
	return Guess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y') || (Response[0] == 'Y');
}
void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You Win\n";
	}
	else
	{
		std::cout << "better luck next time!\n";
	}
}
