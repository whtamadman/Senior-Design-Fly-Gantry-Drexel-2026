#include "pch.h"
#include "BinarySaveData.h"

BinarySaveData::BinarySaveData(const flyViewStruc& fvStruc)
	:
	grabSucceeded(static_cast<bool>(fvStruc.grabSucceeded)),
	imageDamaged(static_cast<bool>(fvStruc.imageDamaged)),
	bottomCamSeesFly(static_cast<bool>(fvStruc.bottomCamSeesFly)),
	bottomCamInCharge(fvStruc.bottomCamInCharge),
	manualOrAuto(fvStruc.manualOrAuto),
	onLED(fvStruc.onLED),
	frameCoMX(fvStruc.frameCoMX),
	frameCoMY(fvStruc.frameCoMY),
	stimulusVoltage(fvStruc.stimulusVoltage),
	absCoMX(fvStruc.absCoMX),
	absCoMY(fvStruc.absCoMY),
	dataNum(fvStruc.dataNum),
	encoderX(fvStruc.encoderX),
	encoderY(fvStruc.encoderY),
	decoderdt(fvStruc.decoderdt),
	camTime(fvStruc.camTime)
{
	const int hours = std::stoi(fvStruc.clockTime.substr(0, 2));
	const int minutes = std::stoi(fvStruc.clockTime.substr(3, 2));
	const int seconds = std::stoi(fvStruc.clockTime.substr(6, 2));
	clockTime = hours * 60 * 60 + minutes * 60 + seconds;
}
