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
#include<ctime>

#ifndef MOVINGOBJECT_H_
#define MOVINGOBJECT_H_

//////////////////////////////////////////
// Class Moving Objects
// A base class for all objects
// that can move across the rooms
//////////////////////////////////////////
class MovingObject {
protected:
	int PosX; // location of the Object
	int PosY; // location of the Object

public:
	// Constructor
	MovingObject();

	// Getters
	int getPosX() {
		return PosX;
	}
	int getPosY() {
		return PosY;
	}

	// Setters
	void setPosX(int x);
	void setPosY(int y);

	void setPosXToRand() {
		PosX = rand() % 8;
	}
	void setPosYToRand() {
		PosY = rand() % 8;
	}

	void move(); // move to a random location
};




#endif /* MOVINGOBJECT_H_ */
