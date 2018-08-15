/////////////////////////////
//Hanna Sasina
//CSS 342
//Assignment# 6
// g++ on Apple
// 5 days, lots of hours!!
/////////////////////////////

#include<iostream>
#include<sstream>
#include<string>
#include<cstdlib>
#include "gameEngine.h"

using namespace std;

// Create Game engine and start the game
int main() {


	// make sure random numbers are really random
	srand(time(NULL));

	GameEngine engine;

	char character;
	do {
		// build maze, print instructions and start the game
		engine.buildMaze();
		engine.printInstructions();
		while (engine.play()) {}
		cout << "Do you want to play again? (Y/N)" << endl;
		cin >> character;
	} while (character == 'Y');



	return 0;
}



