#ifndef DAY_H
#define DAY_H

#include <iostream>

class Day {
    public:
	float open;
	float close;
	float high;
	float low;
	int vol;
	
	//Indicators
	float uBB;
	float lBB;
	float SMA;
	float mSTD;

	//Functions
	Day();
	Day(float c, float h, float l, float o, int v);

};

#endif
