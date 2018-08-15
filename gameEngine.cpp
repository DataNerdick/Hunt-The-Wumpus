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
#include<stdlib.h>
#include<iomanip>
#include<time.h>
#include "gameEngine.h"

using namespace std;

// Constructor
GameEngine :: GameEngine() {
	setMaze();
}
// Destruct the maze
GameEngine :: ~GameEngine() {
	for(int i = 0; i < 8; i++) {
		delete[] maze[i];
	}
	delete[] maze;
}

// Place all objects in the maze at random locations
void GameEngine :: buildMaze() {
	// Clean rooms from previous game
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			maze[i][j].setHasFootPrints(false);
			maze[i][j].setHasPit(false);
		}
	}

	// Put pits in the maze at random locations
	for(int i = 0; i < 4; i++) {
		int x = rand() % 8;
		int y = rand() % 8;
		maze[x][y].setHasPit(true);
	}

	bool heroIsSafe = false;
	// make sure Hero is not placed on a room with Bat,  Pit or Wumpus
	while(!heroIsSafe) {
		// if Hero is placed to the same room where wumpus is located, change the location of the Hero
		if(wumpus.getPosX() == hero.getPosX() && wumpus.getPosY() == hero.getPosY()) {
			// pick new location for the hero
			hero.setPosXToRand();
			hero.setPosYToRand();
			//check again if it is not where wumpus is
			continue;
		}

		// if Hero is placed to the same room where the bats are located, change the location of the Hero
		bool heroInBatsRoom = true;
		while(heroInBatsRoom) {
			int i;
			for(i = 0; i < 4; i++) {
				if(bats[i].getPosX() == hero.getPosX() && bats[i].getPosY() == hero.getPosY()) {
					// pick new location for the Hero, go through all the bats again to make sure that new random
					// location for the Hero did not place him with a bat
					hero.setPosXToRand();
					hero.setPosYToRand();
					break;
				}
			}
			// if i became 4, it means that Hero and all Bats are in different rooms
			if(i == 4)
				heroInBatsRoom = false;
		}

		//if Hero is located to the same place where Pit is located, change the location of the Hero
		if(maze[hero.getPosX()][hero.getPosY()].getHasPit()) { //
			hero.setPosXToRand();
			hero.setPosYToRand();
			continue;
		}

		// after found safe location for the Hero, mark the room with foot prints
		maze[hero.getPosX()][hero.getPosY()].setHasFootPrints(true);
		heroIsSafe = true;
	}
}

// Create the maze and assign numbers to each room
void GameEngine:: setMaze() {
	maze = new Room*[8];
	for(int i = 0; i < 8; i++) {
		maze[i] = new Room[8];
	}
	setRoomNumbers();
}

void GameEngine::setRoomNumbers() {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			maze[i][j].setRoomNumber(8*i + j);
		}
	}
}

int GameEngine::pickRandomPosition() {
	int number;
	number = rand() % 8; // pick number from 0 to 7
	return number;
}

// Move Hero
// If Hero is on the edge of the maze, wrap around the maze
void GameEngine::moveHero(char a) {
	if (a == 'i') { // move up

		if (hero.getPosX() == 0) {
			hero.setPosX(7);
		} else {
			hero.setPosX(hero.getPosX() - 1);
		}
	}

	if (a == 'j') { // move left
		if (hero.getPosY() == 0) {
			hero.setPosY(7);
		} else {
			hero.setPosY(hero.getPosY() - 1);
		}
	}

	if (a == 'm') { // move down
		if (hero.getPosX() == 7) {
			hero.setPosX(0);
		} else {
			hero.setPosX(hero.getPosX() + 1);
		}
	}

	if (a == 'l') { // move right
		if (hero.getPosY() == 7) {
			hero.setPosY(0);
		} else {
			hero.setPosY(hero.getPosY() + 1);
		}
	}
}

// Check if Hero is alive when he moves to a new room
bool GameEngine::didHeroDie() {
	// Check if room has a Wumpus
	if (hero.getPosX() == wumpus.getPosX()
			&& hero.getPosY() == wumpus.getPosY()) {
		cout << "Wumpus got you. GameOver" << endl;
		return true;
	}

	// Check if there are footprints in this room
	if(maze[hero.getPosX()][hero.getPosY()].getHasFootPrints()) {
		cout << "There are footprints in the dust" << endl;
	}

	//Check if room has a pit
	maze[hero.getPosX()][hero.getPosY()].setHasFootPrints(true);
	if (maze[hero.getPosX()][hero.getPosY()].getHasPit()) {
		cout << "You fell into a pit. GameOver" << endl;
		return true;
	}

	// Check if room has a bat
	for (int j = 0; j < 4; j++) {
		// if there is a bat in the room
		if (hero.getPosX() == bats[j].getPosX()
				&& hero.getPosY() == bats[j].getPosY()) {
			cout << "Bat Snatch" << endl;
			// move hero to a random room
			hero.setPosXToRand();
			hero.setPosYToRand();
			// move bat to a random room
			bats[j].setPosXToRand();
			bats[j].setPosYToRand();
			// check if Hero is aslive in the new room
			return didHeroDie();
		}
	}
	return false;
}


// Check what is in the rooms around Hero
void GameEngine::checkNeighbours() {
	// bool values to print only one message for Bats and Pits in case there are multiple
	// bats and pits around the Hero
	bool seenPitsBefore = false;
	bool seenBatsBefore = false;
	// Go around all adjacent rooms and check who is there
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			// do not check diagonal rooms and make sure to stay in the maze boundaries
			if ((abs(i) != abs(j)) && hero.getPosX() + i >= 0
					&& hero.getPosX() + i < 8 && hero.getPosY() + j >= 0
					&& hero.getPosY() + j < 8) {
				// check is there is Wumpus around
				if ((hero.getPosX() + i) == wumpus.getPosX()
						&& (hero.getPosY() + j) == wumpus.getPosY()) {
					cout<< "Smell something rank. (The Wumpus is in an adjacent room)"<< endl;
				}
				// check is there are Pits around
				if (maze[hero.getPosX() + i][hero.getPosY() + j].getHasPit()
						&& !seenPitsBefore) {
					seenPitsBefore = true;
					cout << "Feel a Draft (There is a pit in an adjacent room)"<< endl;
				}
				// check is there are Bats around
				for (int u = 0; u < 4; u++) {
					if ((hero.getPosX() + i) == bats[u].getPosX()
							&& (hero.getPosY() + j) == bats[u].getPosY()
							&& !seenBatsBefore) {
						seenBatsBefore = true;
						cout << "Hear bats in the distance (There are bats in an adjacent room)"<< endl;
					}
				}
			}
		}
	}
}

// shoot the arrow, decrement an arrow, check if killed the Wumpus
// or Wumpus got Hero after Hero shot the arrow.
// returns true or false to the play() method which
// stops or continues the game depending if hero is alive or dead
bool GameEngine:: shootArrow(char c) {
	hero.decrementArrow();
	int X = hero.getPosX();
	int Y = hero.getPosY();

	if(c == 'I') { // shoot up
		X = X - 1;
	}

	if(c == 'J') { // shoot left
		Y = Y-1;
	}

	if(c == 'M') {// shoot down
		X = X+1;
	}

	if(c == 'L') { //shoot right
		Y = Y+1;
	}

	// killed the Wumpus
	if(wumpus.getPosX() == X && wumpus.getPosY() == Y) {
		cout << "You shot the Wumpus!!!!!!!!! YOU WON!!!!!!!" <<endl;
		return false; // stop the game
	}

	// check if have enough arrows
	if(!hero.canShoot()) {
		cout << "You do not have more arrows. GameOver" << endl;
		return false;
	}

	// check if shot into the wall
	if(X < 0 || X > 7 || Y < 0 || Y > 7) {
		cout << "You shot into a wall and lost the arrow" << endl;
		return true;
	}

	// move wumpus at random and check if Hero dies
	moveWumpusAtRandom();
	if(wumpus.getPosX() == hero.getPosX() && wumpus.getPosY() == hero.getPosY()) {
		cout << "Wumpus got you. GameOver" << endl;
		return false; // stop the game
	}

	return true;
}

// Move wumpus to adjacent room at random
void GameEngine:: moveWumpusAtRandom() {
	int position = rand() % 4;
	if(position == 0 && !(wumpus.getPosX() - 1 < 0)) {
		wumpus.setPosX(wumpus.getPosX() - 1);
	}
	if(position == 1 && !(wumpus.getPosY() + 1 > 7)){
		wumpus.setPosY(wumpus.getPosY() + 1);
	}
	if(position == 2 && !(wumpus.getPosX() + 1 > 7)) {
		wumpus.setPosX(wumpus.getPosX() + 1);
	}
	if(position == 3 && !(wumpus.getPosY() - 1 < 0)) {
		wumpus.setPosY(wumpus.getPosY() - 1);
	}
}

void GameEngine:: printInstructions() {
	cout << "Move up, left, right, and down by pressing i, j, l, m" << endl;
	cout << "Type map to print the maze" << endl;
	cout << "Shoot arrow up, left, right, and down by pressing shift i, j, l, m" << endl;
}

void GameEngine:: printMaze() {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			string roomRep;
			if(i == wumpus.getPosX() && j== wumpus.getPosY()) {
				roomRep += "W";
			}
			for(int u = 0; u < 4; u++) {
				if(i == bats[u].getPosX() && j == bats[u].getPosY()) {
					roomRep += "B";
					break;
				}
			}
			if(maze[i][j].getHasPit()) {
				roomRep += "P";
			}

			if(i == hero.getPosX() && j== hero.getPosY()) {
				roomRep += "H";
			}

			if(roomRep == "") {
				cout << std::left << setw(4) << maze[i][j].getRoomNumber();
			}
			else {
				cout << std::left << setw(4) << roomRep;
			}
		}
		cout << endl;
	}
}


// Method that runs the game
bool GameEngine:: play() {
	// after creating the maze and placing objects, check what is around here to print necessary messages
	checkNeighbours();
	// get user input and determine what to do
	string input;
	cin >> input;
	if(input == "map") {
		printMaze();
		return true;
	}


	string validInput[8] = {"i", "j", "m", "l", "I", "J", "M", "L"};
	int i;
	for(i = 0; i < 8; i++) {
		if(validInput[i] == input) {
			break;
		}
	}
	// if the input is not equal to any character in the array, it is a wrong input
	if(i == 8) {
		cout << "Wrong Input" << endl;
		printInstructions();
		return true;
	}

	// if got a small character from the user, move the hero and check if hero is alive
	if(islower(input[0])) {
		moveHero(input[0]);
		bool died = didHeroDie();
		if(!died) {
			cout << "You are in room: "  << maze[hero.getPosX()][hero.getPosY()].getRoomNumber() << endl;
		}
		return !died;
	}

	// if got capital letter from the user, shoot arrow
	else {
		return shootArrow(input[0]);
	}

	return true;
}







