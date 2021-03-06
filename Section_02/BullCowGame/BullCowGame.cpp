#include <iostream>
#include <string>
#include"stdafx.h"

using namespace std;

void PrintIntro();
void PlayGame();
string GetGuess();
bool AskToPlayAgain();

//the entry point for our application
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0;//exit the aplication
}

//introduce the game
void PrintIntro()
{
	constexpr int WORLD_LENGTH = 9;
	cout << "welcome to Bulls and Cows, a fun word game.\n";
	cout << "Can you guess the" << WORLD_LENGTH;
	cout << "letter isogram I'm thinking of?\n";
	cout << endl;
	return;
}

void PlayGame() 
{
	//loop for the number of turns asking for guesses
	constexpr int NUMBER_OF_TURNS = 5;
	for (int count = 1; count <= NUMBER_OF_TURNS; count++)
	{
		string Guess = GetGuess();

		//print guess back
		cout << "Your gues was:" << Guess << endl;
		cout << endl;
	}
}

//get a guess from the player
string GetGuess() 
{
	cout << "enter your guess: ";
	string Guess = "";
	getline(cin, Guess);
	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do you want to play again?";
	string Response = "";
	getline(cin, Response);

	return (Response[0] == 'y')||(Response[0]=='Y');
}
