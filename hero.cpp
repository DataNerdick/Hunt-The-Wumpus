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

using namespace std;

// Constructor
Hero:: Hero(): _arrow(4) {}

// check if has enough arrows to shoot
bool Hero:: canShoot() {
	return _arrow != 0;
}

void Hero:: decrementArrow() {
	_arrow--;
}

