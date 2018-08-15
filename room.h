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
#include"hero.h"
#include"bat.h"
#include"wumpus.h"


#ifndef ROOM_H_
#define ROOM_H_

//////////////////////////////////////////////
//Class Room
//Sets room features
//////////////////////////////////////////////
class Room {

private:
	int _roomNumber;
	bool _hasPit;
	bool _hasFootPrints;

public:
	// Constructor
	Room();

	//getters
	int getRoomNumber() {return _roomNumber;}
	bool getHasPit() {return _hasPit;}
	bool getHasFootPrints() {return _hasFootPrints;}

	// setters
	void setHasPit(bool hasPit);
	void setHasFootPrints(bool footprints);
	void setRoomNumber(int number); // number all the rooms
};




#endif /* ROOM_H_ */
