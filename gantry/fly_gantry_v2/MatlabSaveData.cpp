#include "pch.h"
#include "MatlabSaveData.h"

MatlabSaveData::MatlabSaveData(const char* matFileName, double frequency)
	:
	matFileName(matFileName)
{
	// allocate space for all frame data to be added to during experiment
	const size_t vectorSizeToStart = static_cast<size_t>(70.0 * 60.0 * frequency);

	grabSucceeded.reserve(vectorSizeToStart);
	imageDamaged.reserve(vectorSizeToStart);
	bottomCamSeesFly.reserve(vectorSizeToStart);
	bottomCamInCharge.reserve(vectorSizeToStart);
	manualOrAuto.reserve(vectorSizeToStart);
	onLED.reserve(vectorSizeToStart);
	stimulusVoltage.reserve(vectorSizeToStart);
	frameCoMX.reserve(vectorSizeToStart);
	frameCoMY.reserve(vectorSizeToStart);
	absCoMX.reserve(vectorSizeToStart);
	absCoMY.reserve(vectorSizeToStart);
	dataNum.reserve(vectorSizeToStart);
	encoderX.reserve(vectorSizeToStart);
	encoderY.reserve(vectorSizeToStart);
	decoderdt.reserve(vectorSizeToStart);
	clockTime.reserve(vectorSizeToStart);
	camTime.reserve(vectorSizeToStart);
	stimPointX.reserve(vectorSizeToStart);
	stimPointY.reserve(vectorSizeToStart);
}

// add each frame data to the vectors
void MatlabSaveData::addFrameData(flyViewStruc& fvStruc)
{
	grabSucceeded.push_back(static_cast<unsigned char>(fvStruc.grabSucceeded));
	imageDamaged.push_back(static_cast<unsigned char>(fvStruc.imageDamaged));
	bottomCamSeesFly.push_back(static_cast<unsigned char>(fvStruc.bottomCamSeesFly));
	bottomCamInCharge.push_back(static_cast<unsigned char>(fvStruc.bottomCamInCharge));
	manualOrAuto.push_back(static_cast<unsigned char>(fvStruc.manualOrAuto));
	onLED.push_back(static_cast<unsigned char>(fvStruc.onLED));
	stimulusVoltage.push_back(fvStruc.stimulusVoltage);
	frameCoMX.push_back(fvStruc.frameCoMX);
	frameCoMY.push_back(fvStruc.frameCoMY);
	absCoMX.push_back(fvStruc.absCoMX);
	absCoMY.push_back(fvStruc.absCoMY);
	stimPointX.push_back(fvStruc.stimPointX);
	stimPointY.push_back(fvStruc.stimPointY);
	dataNum.push_back(fvStruc.dataNum);
	encoderX.push_back(fvStruc.encoderX);
	encoderY.push_back(fvStruc.encoderY);
	decoderdt.push_back(fvStruc.decoderdt);
	const int hours = std::stoi(fvStruc.clockTime.substr(0, 2));
	const int minutes = std::stoi(fvStruc.clockTime.substr(3, 2));
	const int seconds = std::stoi(fvStruc.clockTime.substr(6, 2));
	const int timeInSeconds = hours * 60 * 60 + minutes * 60 + seconds;
	clockTime.push_back(timeInSeconds);
	camTime.push_back(fvStruc.camTime);
}

// save data from each vector into the mat file using MATLAB API C functions
void MatlabSaveData::saveMatFile()
{	
	MATFile* pmat = matOpen(matFileName, "w");

	const size_t numberOfFrames = grabSucceeded.size();

	mxArray* logicalArray = mxCreateLogicalMatrix(numberOfFrames, 1);
	mxArray* floatArray = mxCreateNumericMatrix(numberOfFrames, 1, mxSINGLE_CLASS, mxREAL);
	mxArray* int32Array = mxCreateNumericMatrix(numberOfFrames, 1, mxINT32_CLASS, mxREAL);
	mxArray* uint32Array = mxCreateNumericMatrix(numberOfFrames, 1, mxUINT32_CLASS, mxREAL);
	mxArray* uint64Array = mxCreateNumericMatrix(numberOfFrames, 1, mxUINT64_CLASS, mxREAL);

	void* logicalArrayPtr = static_cast<void*>(mxGetPr(logicalArray));
	void* floatArrayPtr = static_cast<void*>(mxGetPr(floatArray));
	void* int32ArrayPtr = static_cast<void*>(mxGetPr(int32Array));
	void* uint32ArrayPtr = static_cast<void*>(mxGetPr(uint32Array));
	void* uint64ArrayPtr = static_cast<void*>(mxGetPr(uint64Array));

	memcpy(logicalArrayPtr, static_cast<const void*>(grabSucceeded.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "grabSucceeded", logicalArray);

	memcpy(logicalArrayPtr, static_cast<const void*>(imageDamaged.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "imageDamaged", logicalArray);

	memcpy(logicalArrayPtr, static_cast<const void*>(bottomCamSeesFly.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "bottomCamSeesFly", logicalArray);

	memcpy(logicalArrayPtr, static_cast<const void*>(bottomCamInCharge.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "bottomCamInCharge", logicalArray);

	memcpy(logicalArrayPtr, static_cast<const void*>(manualOrAuto.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "manualOrAuto", logicalArray);

	memcpy(logicalArrayPtr, static_cast<const void*>(onLED.data()), numberOfFrames * sizeof(unsigned char));
	matPutVariable(pmat, "onLED", logicalArray);

	memcpy(floatArrayPtr, static_cast<const void*>(stimulusVoltage.data()), numberOfFrames * sizeof(float));
	matPutVariable(pmat, "stimulusVoltage", floatArray);

	memcpy(int32ArrayPtr, static_cast<const void*>(frameCoMX.data()), numberOfFrames * sizeof(int32_t));
	matPutVariable(pmat, "frameCoMX", int32Array);

	memcpy(int32ArrayPtr, static_cast<const void*>(frameCoMY.data()), numberOfFrames * sizeof(int32_t));
	matPutVariable(pmat, "frameCoMY", int32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(stimPointX.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "stimPointX", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(stimPointY.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "stimPointY", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(absCoMX.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "absCoMX", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(absCoMY.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "absCoMY", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(dataNum.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "dataNum", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(encoderX.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "encoderX", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(encoderY.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "encoderY", uint32Array);

	memcpy(uint32ArrayPtr, static_cast<const void*>(decoderdt.data()), numberOfFrames * sizeof(uint32_t));
	matPutVariable(pmat, "decoderdt", uint32Array);

	memcpy(int32ArrayPtr, static_cast<const void*>(clockTime.data()), numberOfFrames * sizeof(int32_t));
	matPutVariable(pmat, "clockTime", int32Array);

	memcpy(uint64ArrayPtr, static_cast<const void*>(camTime.data()), numberOfFrames * sizeof(uint64_t));
	matPutVariable(pmat, "camTime", uint64Array);

	matClose(pmat);

	mxDestroyArray(logicalArray);
	mxDestroyArray(floatArray);
	mxDestroyArray(int32Array);
	mxDestroyArray(uint32Array);
	mxDestroyArray(uint64Array);
}


//std::vector<bool> grabSucceeded;
//std::vector<bool> imageDamaged;
//std::vector<bool> bottomCamSeesFly;
//std::vector<bool> bottomCamInCharge;
//std::vector<bool> manualOrAuto;
//std::vector<bool> onLED;
//std::vector<float> stimulusVoltage;
//std::vector<int32_t> frameCoMX;
//std::vector<int32_t> frameCoMY;
//std::vector<uint32_t> absCoMX;
//std::vector<uint32_t> absCoMY;
//std::vector<uint32_t> dataNum;
//std::vector<uint32_t> encoderX;
//std::vector<uint32_t> encoderY;
//std::vector<uint32_t> decoderdt;
//std::vector<int32_t> clockTime;
//std::vector<uint64_t> camTime;
