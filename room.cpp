/////////////////////////////
//Hanna Sasina
//CSS 342
//Assignment# 6
// g++ on Apple
// 5 days, lots of hours!!
/////////////////////////////
#include<sstream>
#include<string>
#include"room.h"

using namespace std;


// Constructor
Room::Room() :  _roomNumber(0),
		_hasPit(false), _hasFootPrints(false) {
}
// Destructor

void Room:: setHasPit(bool hasPit) {
	_hasPit = hasPit;
}

void Room:: setHasFootPrints(bool footprints) {
	_hasFootPrints = footprints;
}
// assign number to each room
void Room:: setRoomNumber(int number) {
	_roomNumber = number;
}







