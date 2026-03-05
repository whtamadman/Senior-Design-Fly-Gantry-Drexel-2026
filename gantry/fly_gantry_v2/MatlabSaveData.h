#pragma once

#include <mat.h>
#include <vector>
#include "flyViewStruc.h"

// see documentation for MATLAB data API using C
class MatlabSaveData
{
public:
	MatlabSaveData(const char* matFileName, double frequency);
	void addFrameData(flyViewStruc& fvStruc);
	void saveMatFile();
private:
	const char* matFileName;
	// vectors to hold all data for each frame to be saved to mat file at the end
	std::vector<unsigned char> grabSucceeded;
	std::vector<unsigned char> imageDamaged;
	std::vector<unsigned char> bottomCamSeesFly;
	std::vector<unsigned char> bottomCamInCharge;
	std::vector<unsigned char> manualOrAuto;
	std::vector<unsigned char> onLED;
	std::vector<float> stimulusVoltage;
	std::vector<int32_t> frameCoMX;
	std::vector<int32_t> frameCoMY;
	std::vector<uint32_t> absCoMX;
	std::vector<uint32_t> absCoMY;
	std::vector<uint32_t> dataNum;
	std::vector<uint32_t> encoderX;
	std::vector<uint32_t> encoderY;
	std::vector<uint32_t> decoderdt;
	std::vector<int32_t> clockTime;
	std::vector<uint64_t> camTime;
	std::vector<uint32_t> stimPointX;
	std::vector<uint32_t> stimPointY;
};

