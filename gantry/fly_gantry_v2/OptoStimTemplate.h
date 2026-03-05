#pragma once

#include <fstream>
#include <string>
#include <random>
#include "gantry.h"
#include "WindowManager.h"
#include "topCamProc.h"
class ArenaProc;

enum StimulusType
{
	CircleStimulus,
	//LineStimulus
	//Added by Marcello for White Noise stim pattern.
	LineStimulus,
	WhiteNoiseStimulus,
};

class OptoStim
{
private:
	enum ExperimentState
	{
		preOpto,
		pulseOn,
		pulseInterval,
		zone
	};
public:
	OptoStim(Gantry& motors_in, double frequency, WindowManager& wnd_in, StimulusType stimType_in);
	~OptoStim();
	void setStimulus(long long encoderX, long long encoderY, bool bottomCamFlyFound);
	void setOptoZone(float x, float y);
	bool getStimulusOnState();
	bool usingOptogenetics();
	bool isInStimulusZone(long long encoderX, long long encoderY);
	bool isInStimulusZone(float encoderX, float encoderY);
	bool isInStimulusZone(int encoderX, int encoderY);
	// Added by Marcello
	bool isInStimulusZone(int randomWalk);
	void setArenaCenter(float x, float y);
	StimulusType getStimulusType();
	void setArenaPReference(ArenaProc* arenaP_in);
	char* getTimerString();
	bool isTimerRunning();
	float getMaxVoltage();
	double getStimulusWidth();
public:
	long long center[2];
	double slope;
	static constexpr float diameterCM = 2.5f;
	static constexpr long long distance = (long long)((diameterCM / 2.0f) * 10000.0f);
	static constexpr long long distanceSquared = distance * distance;
private:
	void setOnVoltage();
	void setOffVoltage();
	void setCircularOptoZone(float x, float y);
	void setLinearOptoZone(float x, float y);
	void runTimer(long long encoderX, long long encoderY, bool bottomCamFlyFound);
private:
	class stimulusLineBreak {
	public:
		stimulusLineBreak(long long x, long long y, int offTimerMax_in, double frequency);
		bool isWithinOffZone(long long encoderX, long long encoderY);
		bool timerDone(ArenaProc* arenaP);
	private:
		int offTimeMaxFrames;
		int onTimer = 0;
		int offTimer = 0;
		long long offStartLocationX;
		long long offStartLocationY;
		int onTimerMax;
		static constexpr int offTimeMaxSeconds = 60;
		bool onTimerRunning = true;
		bool offTimerRunning = false;
	};
private:
	static constexpr float LED_617_Voltage = 3.5f;
	static constexpr float rampUpTime = 100.0; //ms
	float voltageStep;
	std::fstream saveFile;
	bool stimulusOnState;
	float voltage = 0.0f;
	Gantry& motors;
	WindowManager& wnd;
	ArenaProc* arenaP;
	bool optoState = false;
	bool useOptogenetics = false;
	bool constantOn = false;
	bool constantOnState = false;
	StimulusType stimType;
	long long arenaCenter[2];
	static constexpr double stimulusLineWidth = 2000;
	static constexpr double stimulusLineWidthSquared = stimulusLineWidth * stimulusLineWidth;
	static constexpr long long maxDistanceFromCenter = 260000 / 2;
	static constexpr long long maxDistanceFromCenterSquared = maxDistanceFromCenter * maxDistanceFromCenter;
	unsigned int timer = 0;
	// Added by Marcello for white noise stimulus type
	unsigned int randomWalk = 0;
	static constexpr unsigned int maxTimeMinutes = 15; //min
	static constexpr unsigned int numberOfPulses = 5;
	static constexpr unsigned int pulseIntervalLength = 5; //s
	static constexpr double pulseLength = 0.1; //s
	unsigned int maxTimerPart1;
	unsigned int maxTimerPart2;
	unsigned int pulseTimer = 0;
	unsigned int pulseIntervalTimer = 0;
	unsigned int pulseTimerEndValue;
	unsigned int pulseIntervalEndValue;
	ExperimentState experimentState = preOpto;
	double frequency;
	std::mt19937 rng;
	std::uniform_int_distribution<int> offTimeDistribution;
	std::vector<stimulusLineBreak> stimulusLineBreaks;
	static constexpr long long offWidthInCM = 1;
	static constexpr long long offWidthInMicrometers = offWidthInCM * 10000;
	static constexpr long long maxDistanceFromOffLocationSquared = (offWidthInMicrometers / 2) * (offWidthInMicrometers / 2);
	static constexpr int maxTimeBeforeOffSeconds = 5;
};
