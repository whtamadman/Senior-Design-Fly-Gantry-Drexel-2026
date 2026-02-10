#pragma once
#include <iostream>
#include <vector>
class Position {
private:

	unsigned long absC; //incoming (current) count value
	unsigned long absPrev; //prevous count value
	unsigned long lcntIn; //incoming (current) latched count value
	unsigned long lcntPrev; //prevous latched count value
	int zoneLength;
	int zoneLengthSigned;
	int sgn(double v);

public:
	Position();
	bool calibrated;
	unsigned long getAbsPos(unsigned long cnt);
	void feedInLCnt(unsigned long lcnt);
	unsigned long numIdx; //number of times encoder encountered indices;
	bool setForAcquisition;
	bool onY;
	bool getAbsPos_NeverCalled; // tell the main code to setup acquisition
	int gain;
	bool eStopUp;
	bool eStopDown;
};