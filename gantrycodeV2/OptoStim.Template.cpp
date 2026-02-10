#include "pch.h"
#include "OptoStim.h"
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>


OptoStim::OptoStim(Gantry& motors_in, double frequency, WindowManager& wnd_in, StimulusType stimType_in)
	: motors(motors_in), wnd(wnd_in), stimType(stimType_in), frequency(frequency)
{
	std::random_device rd;
	rng = std::mt19937(rd());
	offTimeDistribution = std::uniform_int_distribution<int>((int)frequency, maxTimeBeforeOffSeconds * (int)frequency);
	std::default_random_engine generator;
  std::uniform_int_distribution<int> distribution(0,1);
	switch (stimType)
	{
	case CircleStimulus:
	{
		saveFile.open("OptoCenter.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string coordinate;
			int n = 0;
			while (std::getline(saveFile, coordinate))
			{
				center[n] = std::stoi(coordinate);
				n++;
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open OptoCenter file" << std::endl;
		}
		break;
	}
	case LineStimulus:
	{
		saveFile.open("OptoSlope.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string slopeString;
			while (std::getline(saveFile, slopeString))
			{
				slope = std::stod(slopeString);
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open OptoSlope file" << std::endl;
		}
		break;
	}

	//case WhiteNoiseStimulus added by Marcello
	case WhiteNoiseStimulus:
	{
		saveFile.open("OptoWhiteNoise.txt",std::ios::in);
		std::stringline;
		if (saveFile.is_open())
		{
			std:string paramString;
			while (std::getline(saveFile,paramString))
			{
				param = std::stod(paramString);
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open noise OptoWhiteNoise file" << std::endl;
		}
		break;
	}
	//case WhiteNoiseStimulus added by Marcello
	case WhiteNoiseStimulus:
	{
		saveFile.open("OptoPulses.txt", std::ios::in);
		std::stringline;
		if (saveFile.is_open())
		{
		std:string paramString;
			while (std::getline(saveFile, paramString))
			{
				param = std::stod(paramString);
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open noise OptoWhiteNoise file" << std::endl;
		}
		break;
	}
	}
	voltageStep = (LED_617_Voltage / rampUpTime) * (1000.0f / 1.0f) * (1.0f / float(frequency));

	maxTimerPart1 = (unsigned int)frequency * maxTimeMinutes * 60;
	maxTimerPart2 = maxTimerPart1 + (numberOfPulses * pulseIntervalLength * (unsigned int)frequency) + (unsigned int)(pulseLength * frequency) * numberOfPulses;

	pulseTimerEndValue = (unsigned int)(pulseLength * frequency);
	pulseIntervalEndValue = pulseIntervalLength * (unsigned int)frequency;
}


OptoStim::~OptoStim()
{
}

void OptoStim::setStimulus(long long encoderX, long long encoderY, bool bottomCamFlyFound)
{
	if (wnd.keyPressed(0x4F)) //O
	{
		if (!optoState)
		{
			useOptogenetics = !useOptogenetics;
			experimentState = zone;
			arenaP->setOptoZoneViewMat();
		}
		optoState = true;
	}
	else
	{
		optoState = false;
	}

	if (wnd.keyPressed(0x54)) //T
	{
		useOptogenetics = true;
	}

	if (!useOptogenetics)
	{
		stimulusOnState = false;
		return;
	}
	else
	{
		runTimer(encoderX, encoderY, bottomCamFlyFound);
		if (wnd.keyPressed(0x50)) //P
		{
			if (!constantOnState)
			{
				constantOn = !constantOn;
			}
			constantOnState = true;
		}
		else
		{
			constantOnState = false;
		}
	}
	const bool stimulusPreviousOnState = stimulusOnState;
	stimulusOnState = constantOn || (experimentState == pulseOn) || (experimentState == zone && bottomCamFlyFound && isInStimulusZone(encoderX, encoderY));

	for (std::vector<stimulusLineBreak>::iterator it = stimulusLineBreaks.begin(); it != stimulusLineBreaks.end(); )
	{
		if (it->timerDone(arenaP))
		{
			it = stimulusLineBreaks.erase(it);
			arenaP->setOptoZoneViewMat();
		}
		else
		{
			it++;
		}
	}

	if (stimulusOnState)
	{
		if (!stimulusPreviousOnState && experimentState == zone && !constantOn)
		{
			stimulusLineBreaks.push_back(stimulusLineBreak(encoderX, encoderY, offTimeDistribution(rng), frequency));
		}

		setOnVoltage();
	}
	else
	{
		setOffVoltage();
	}
}

bool OptoStim::getStimulusOnState()
{
	return stimulusOnState;
}

bool OptoStim::usingOptogenetics()
{
	return useOptogenetics;
}

bool OptoStim::isInStimulusZone(long long encoderX, long long encoderY)
{
	switch (stimType)
	{
	case CircleStimulus:
	{
		const long long xDistance = center[0] - encoderX;
		const long long yDistance = center[1] - encoderY;

		const long long xDistanceSquared = xDistance * xDistance;
		const long long yDistanceSquared = yDistance * yDistance;

		const long long sumDistanceSquared = xDistanceSquared + yDistanceSquared;

		return sumDistanceSquared < distanceSquared;
	}
	case LineStimulus:
	{
		if (experimentState != zone)
		{
			return false;
		}
		else
		{
			const long long xDistanceFromCenter = encoderX - arenaCenter[0];
			const long long yDistanceFromCenter = encoderY - arenaCenter[1];

			const long long xDistanceFromCenterSquared = xDistanceFromCenter * xDistanceFromCenter;
			const long long yDistanceFromCenterSquared = yDistanceFromCenter * yDistanceFromCenter;
			const long long sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;

			// d = |mx - y| / sqrt(m^2 + 1)
			const double numerator = slope * (double)xDistanceFromCenter - (double)yDistanceFromCenter;
			const double numeratorSquared = numerator * numerator;
			const double denominatorSquared = slope * slope + 1.0;
			const double distanceFromLineSquared = numeratorSquared / denominatorSquared;

			bool withinBoundary = (distanceFromLineSquared <= stimulusLineWidthSquared / 4) && (sumDistanceFromCenterSquared <= maxDistanceFromCenterSquared);

			if (withinBoundary)
			{
				for (std::vector<stimulusLineBreak>::iterator it = stimulusLineBreaks.begin(); it != stimulusLineBreaks.end(); ++it)
				{
					if (it->isWithinOffZone(encoderX, encoderY))
					{
						return false;
					}
				}
			}
			return withinBoundary;
		}
	}
	case WhiteNoiseStimulus:
	{
		int roll = distribution(generator);
		return roll >= 1;
	}
	}
	
	
}

bool OptoStim::isInStimulusZone(float encoderX, float encoderY)
{
	return isInStimulusZone((long long)encoderX, (long long)encoderY);
}

bool OptoStim::isInStimulusZone(int encoderX, int encoderY)
{
	return isInStimulusZone((long long)encoderX, (long long)encoderY);
}

void OptoStim::setArenaCenter(float x, float y)
{
	arenaCenter[0] = (long long)x;
	arenaCenter[1] = (long long)y;
}

StimulusType OptoStim::getStimulusType()
{
	return stimType;
}

void OptoStim::runTimer(long long encoderX, long long encoderY, bool bottomCamFlyFound)
{
	switch (experimentState)
	{
	case OptoStim::preOpto:
		timer++;
		if (timer == maxTimerPart1)
		{
			const long long xDistanceFromCenter = encoderX - arenaCenter[0];
			const long long yDistanceFromCenter = encoderY - arenaCenter[1];

			const long long xDistanceFromCenterSquared = xDistanceFromCenter * xDistanceFromCenter;
			const long long yDistanceFromCenterSquared = yDistanceFromCenter * yDistanceFromCenter;
			const long long sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;
			if (sumDistanceFromCenterSquared <= maxDistanceFromCenterSquared && bottomCamFlyFound)
			{
				experimentState = pulseOn;
			}
			else
			{
				timer--;
			}
		}
		break;
	case OptoStim::pulseOn:

		{
			timer++;
			pulseTimer++;
		}
		if (pulseTimer == pulseTimerEndValue)
		{
			pulseTimer = 0;
			experimentState = pulseInterval;
		}
		break;
	case OptoStim::pulseInterval:
		timer++;
		pulseIntervalTimer++;
		if (timer == maxTimerPart2)
		{
			const long long xDistanceFromCenter = encoderX - arenaCenter[0];
			const long long yDistanceFromCenter = encoderY - arenaCenter[1];

			const long long xDistanceFromCenterSquared = xDistanceFromCenter * xDistanceFromCenter;
			const long long yDistanceFromCenterSquared = yDistanceFromCenter * yDistanceFromCenter;
			const long long sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;

			if (sumDistanceFromCenterSquared <= maxDistanceFromCenterSquared && bottomCamFlyFound)
			{
				setLinearOptoZone((float)encoderX, (float)encoderY);
				experimentState = zone;
				arenaP->setOptoZoneViewMat();
			}
			else
			{
				timer--;
				pulseIntervalTimer--;
			}
		}
		else if (pulseIntervalTimer == pulseIntervalEndValue)
		{
			const long long xDistanceFromCenter = encoderX - arenaCenter[0];
			const long long yDistanceFromCenter = encoderY - arenaCenter[1];

			const long long xDistanceFromCenterSquared = xDistanceFromCenter * xDistanceFromCenter;
			const long long yDistanceFromCenterSquared = yDistanceFromCenter * yDistanceFromCenter;
			const long long sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;
			if (sumDistanceFromCenterSquared <= maxDistanceFromCenterSquared && bottomCamFlyFound)
			{
				experimentState = pulseOn;
				pulseIntervalTimer = 0;
			}
			else
			{
				timer--;
				pulseIntervalTimer--;
			}
		}
		break;
	case OptoStim::zone:
		break;
	}
}

char* OptoStim::getTimerString()
{
	char timerString[6];
	if (timer < maxTimerPart1 - 1)
	{
		const unsigned int timerInSeconds = timer / (unsigned int)frequency;
		const unsigned int timeRemaining = maxTimeMinutes * 60 - timerInSeconds;
		const unsigned int minutesRemaining = timeRemaining / 60;
		const unsigned int remainderSeconds = timeRemaining % 60;
		std::sprintf(timerString, "%02d:%02d", minutesRemaining, remainderSeconds);
	}
	else
	{
		strcpy(timerString, "00:00");
	}

	return timerString;
}

bool OptoStim::isTimerRunning()
{
	return timer < maxTimerPart2;
}

float OptoStim::getMaxVoltage()
{
	return LED_617_Voltage;
}

double OptoStim::getStimulusWidth()
{
	return stimulusLineWidth;
}

void OptoStim::setOnVoltage()
{
	if (voltage < LED_617_Voltage)
	{
		voltage += voltageStep;
	}
	motors.DriveOptoLED(voltage);
}

void OptoStim::setOffVoltage()
{
	if (voltage > 0)
	{
		voltage -= voltageStep;
		motors.DriveOptoLED(voltage);
	}
	else
	{
		motors.StopOptoLED();
	}
}

void OptoStim::setOptoZone(float x, float y)
{
	switch (stimType)
	{
	case CircleStimulus:
		setCircularOptoZone(x, y);
		break;
	case LineStimulus:
		setLinearOptoZone(x, y);
		break;
	default:
		break;
	}
}

void OptoStim::setCircularOptoZone(float x, float y)
{
	center[0] = long long(x);
	center[1] = long long(y);

	saveFile.open("OptoCenter.txt", std::ios::out);

	if (saveFile.is_open())
	{
		saveFile << center[0] << "\n" << center[1] << "\n";
		saveFile.close();
	}
	else
	{
		std::cout << "Could not open OptoCenter.txt to save stimulation location" << std::endl;
	}
}

void OptoStim::setLinearOptoZone(float x, float y)
{
	slope = ((double)y - (double)arenaCenter[1]) / ((double)x - (double)arenaCenter[0]);
	saveFile.open("OptoSlope.txt", std::ios::out);

	if (saveFile.is_open())
	{
		saveFile << slope;
		saveFile.close();
	}
	else
	{
		std::cout << "Could not open OptoSlope.txt to save stimulus slope" << std::endl;
	}
}

void OptoStim::setArenaPReference(ArenaProc* arenaP_in)
{
	arenaP = arenaP_in;
}

OptoStim::stimulusLineBreak::stimulusLineBreak(long long x, long long y, int offTimerMax_in, double frequency)
	: offStartLocationX(x), offStartLocationY(y), onTimerMax(offTimerMax_in), offTimeMaxFrames((int)frequency * offTimeMaxSeconds)
{

}

bool OptoStim::stimulusLineBreak::isWithinOffZone(long long encoderX, long long encoderY)
{
	if (onTimerRunning)
	{
		return false;
	}
	else
	{
		const long long xDistanceFromPoint = encoderX - offStartLocationX;
		const long long yDistanceFromPoint = encoderY - offStartLocationY;

		const long long xDistanceFromPointSquared = xDistanceFromPoint * xDistanceFromPoint;
		const long long yDistanceFromPointSquared = yDistanceFromPoint * yDistanceFromPoint;
		const long long sumDistanceFromPointSquared = xDistanceFromPointSquared + yDistanceFromPointSquared;

		return sumDistanceFromPointSquared < maxDistanceFromOffLocationSquared;
	}
}


bool OptoStim::stimulusLineBreak::timerDone(ArenaProc* arenaP)
{
	if (onTimer < onTimerMax)
	{
		onTimer++;
	}
	else if (onTimer == onTimerMax)
	{
		onTimer++;
		onTimerRunning = false;
		offTimerRunning = true;
		arenaP->setOptoZoneViewMat();
	}
	else if (offTimer < offTimeMaxFrames)
	{
		offTimer++;
	}
	else if (offTimer == offTimeMaxFrames)
	{
		return true;
	}
	return false;
}
