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
#include"movingObject.h"

// Constructor
MovingObject :: MovingObject(){
	setPosXToRand(); // pick number from 1 to 8
	setPosYToRand();
}

void MovingObject :: setPosX(int x) {
	PosX = x;
}

void MovingObject :: setPosY(int y) {
	PosY = y;
}


