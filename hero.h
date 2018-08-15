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

#ifndef HERO_H_
#define HERO_H_

//////////////////////////////////////////////
//Class Hero
//Extends the MovingObject Class
//With additional features to handle arrows
//////////////////////////////////////////////
class Hero: public MovingObject {
private:
	int _arrow;
public:
	// Constructor
	Hero();
    bool canShoot();
    void decrementArrow();
};


#endif /* HERO_H_ */
