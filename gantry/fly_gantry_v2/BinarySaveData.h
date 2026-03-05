#pragma once
#include <cstdint>
#include "flyViewStruc.h"
class BinarySaveData
{
public:
	BinarySaveData(const flyViewStruc& fvStruc);
private:
	bool grabSucceeded;
	bool imageDamaged;
	bool bottomCamSeesFly;
	bool bottomCamInCharge;
	bool manualOrAuto;
	bool onLED;

	float stimulusVoltage;

	int32_t frameCoMX;
	int32_t frameCoMY;
	uint32_t absCoMX;
	uint32_t absCoMY;
	uint32_t dataNum;
	uint32_t encoderX;
	uint32_t encoderY;
	uint32_t decoderdt;
	int32_t clockTime;
	uint64_t camTime;
};

