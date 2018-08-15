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
#include"room.h"

#ifndef GAMEENGINE_H_
#define GAMEENGINE_H_

////////////////////////////////////////////////////////////
// Class Game Engine
// Creates the maze and objects that move
// across the maze. Has the methods that control the game
////////////////////////////////////////////////////////////
class GameEngine {
private:
	Room **maze; // array of rooms
	Wumpus wumpus;
	Bat bats[4];
	Hero hero;

public:
	// construct the maze
	GameEngine();
	virtual ~GameEngine();

	void buildMaze();
	void setMaze();
	void setRoomNumbers();
	int pickRandomPosition();
	void moveHero(char a);
	bool didHeroDie();
	void checkNeighbours();
	bool shootArrow(char c);
	void moveWumpusAtRandom();
	void printInstructions();
	void printMaze();
	bool play();
};

#endif /* GAMEENGINE_H_ */
