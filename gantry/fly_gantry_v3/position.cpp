#include "pch.h"
#include "position.h"
#include <math.h>

//Preset value needs to be set!
Position::Position()
{
	absC = 0; //incoming (current) count value
	absPrev = 0; //prevous count value
	lcntIn = 0;
	lcntPrev = 0;
	numIdx = 0; //number of times encoder encountered index
	calibrated = false;
	getAbsPos_NeverCalled = true;
	setForAcquisition = false;
	gain = 0;
	eStopUp = false;
	eStopDown = false;
}

unsigned long Position::getAbsPos(unsigned long cnt)
{
	absC = cnt + gain;

	if (absC != absPrev)
	{
		//std::cout << absC << std::endl;
		absPrev = absC;
	}

	if (absC >= 400000)
	{
		eStopUp = true;
	}
	else
	{
		eStopUp = false;
	}

	if (absC <= 45000)
	{
		eStopDown = true;
	}
	else
	{
		eStopDown = false;
	}

	getAbsPos_NeverCalled = false;
	return absC;
}

void Position::feedInLCnt(unsigned long lcnt)
{
	lcntIn = lcnt;
	//int sign = 1;
	double AbsPosPrev = 0;
	double P = 2.0 * 1000; // pole length is 2mm
	double K = 48.0 * 1000; // K is 48mm
	double D = 1.0; //direction of movement
	double dR = 0.0;

	std::vector<int> possibleZLengths{ 28000 , 20000, 30000, 18000, 32000, 16000, 34000 };

	if (lcntIn != lcntPrev)
	{
		// we can get realiable zoneLength only after passing index value certain amount of times.
		// Practically, 4 times.
		if (numIdx >= 3)
		{
			if (lcntPrev > lcntIn)
			{
				zoneLength = lcntPrev - lcntIn;
				D = -1;
			}
			else
			{
				zoneLength = lcntIn - lcntPrev;
				D = 1;
			}

			zoneLengthSigned = D * 1.0 * zoneLength;

			//std::cout << zoneLengthSigned << std::endl;

			if (find(possibleZLengths.begin(), possibleZLengths.end(), zoneLength) != possibleZLengths.end())
			{
				dR = zoneLength;
				AbsPosPrev = (1/P * abs(2* dR -K)-sgn(2* dR -K)-1)*K/2 + (sgn(2* dR -K)-sgn(D))*abs(dR)/2;

				gain = AbsPosPrev - lcntPrev;

				std::cout << zoneLengthSigned << " " << lcntPrev << " " << AbsPosPrev << " " << lcntPrev + gain << std::endl;
				
				calibrated = true;
			}
		}

		lcntPrev = lcntIn;
		numIdx++;
	}

}

int Position::sgn(double v) {
	if (v < 0) return -1;
	if (v > 0) return 1;
	return 0;
}
