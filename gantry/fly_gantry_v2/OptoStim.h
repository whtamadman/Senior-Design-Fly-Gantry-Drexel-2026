#pragma once

#include <fstream>
#include <string>
#include <random>
#include "gantry.h"
#include "WindowManager.h"
#include "topCamProc.h"
#include "Config.h"
class ArenaProc;

enum StimulusType
{
	CircleStimulus,
	LineStimulus,
	ConcentricCircleStimulus,
	//Added By Marcello 10/02/22
	WhiteNoiseStimulus,
	PulseStimulus,
	CrudePlume,
	probPlume,
	PatternFromFile
};

class OptoStim
{
private:
	// used to set what is happening in the experiment
	enum ExperimentState
	{
		preOpto, // before the baseline period timer runs out
		pulseOn, // an automated pulse is stimulating the fly
		pulseInterval, // between automated pulses
		zone // stimulus zone is defined
	};
	// for old way of doing gradient stimulus
//	class RandomStimulusTimer
//	{
//	public:
//		RandomStimulusTimer(double frequency);
//		float runTimer(float voltageStep);
//	private:
//		int rampUpTimer = 0;
//		int rampDownTimer = 0;
//		float randomStimulusTimerVoltage = 0.0f;
//		int maxRampFrames;
//	};
public:
	OptoStim(Gantry& motors_in, double frequency, WindowManager& wnd_in, Config& config_in);
	~OptoStim();
	void setStimulus(long long encoderX, long long encoderY, bool bottomCamFlyFound);
	void setOptoZone(float x, float y);
	bool getStimulusOnState();
	bool usingOptogenetics();
	bool isInStimulusZone(long long encoderX, long long encoderY, bool pflag);
	bool isInStimulusZone(float encoderX, float encoderY, bool pflag);
	bool isInStimulusZone(int encoderX, int encoderY, bool pflag);
	void setArenaCenter(float x, float y);
	StimulusType getStimulusType();
	void setArenaPReference(ArenaProc* arenaP_in);
	char* getTimerString();
	bool isTimerRunning();
	float getMaxVoltage();
	double getStimulusWidth();
	float getStimulusVoltage();
	long long getSmallerCircleRadius();
public:
	long long center[2]; // center of the stimulus circle
	double slope; // slope of the rectangle
	double slopePars[7]; //Added by Marcello: Controls timers for discontinuous stimulus
	float diameterCM; // diameter of stimulus circle
	long long circleRadius; // radius of stimulus circle
	long long circleRadiusSquared;
	// Added by Marcello

	std::vector<bool> pattern; //For reading in stimulus from file
	double noiseParams[3]; //For use in Noise stimulus
	double plumePars[7]; //For the crude plume
	double pPlumePars[5];
	double uSlope;
	double lSlope; //For the crude plume, converts angles to slopes.
	double distanceFromCircle; //need a double since long is an int type, undefined sqrt
	long long xDistSquared;
	long long yDistSquared;
	double distanceToEdge;
	double angDist; //angular distance to center of plume
	double onPeriod;
	double offPeriod;
	double diffusivity; //measure of crosswind mixing. Decrease to increase plume width.
	double radSegments;  //base Light duty cycle, radial segments to increase light on frequency.
	double thisOff; //Light refractory period based on distance to odor source
	
	

	bool aboveLower;
	bool belowUpper;
	double segmentLength;
	double proportion;
	double thisSegment;
	double xDist;
	double yDist;
	int flipStim;
	//std::ofstream outFile; // Text output for stim debugging
	//std::ofstream outFile2; // Use these to print out various timestamps/ms counts/on states etc
	//std::ofstream outFile3;

	

	unsigned int times[4]; //For use in pulses
	//various on/off flags used for non-location related lights
	bool pulseStimOn = false;
	bool pulseStimOff = false;
	bool carrierStimOn = false;
	bool carrierStimOff = false;
	bool entryReady = true;
	bool burstMode = false;
	std::chrono::high_resolution_clock::time_point startPulseTime;
	std::chrono::high_resolution_clock::time_point currentTime;
	std::chrono::high_resolution_clock::time_point startCarrierTime;
	std::chrono::milliseconds elapsedPulse;
	std::chrono::milliseconds elapsedCarrier;
	//unsigned int pulses = 1; //placeholder for debugging
private:
	void setConfigParameters();
	void setOnVoltage(bool distanceBased);
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
	float LED_617_Voltage; // maximum voltage to stimulus LED
	//static constexpr float rampUpTime = 100.0; // amount of time to ramp up to and down from max voltage in ms
	float rampUpTime; //Changed by Marcello, 100 ms ramp up time is too long for short-duration stimuli, rampUpTime now set in gantryConfig.txt
	float voltageStep; // how much to change the voltage in each frame during ramp up or down
	std::fstream saveFile; // for saving previously used stimulus location to a file
	bool stimulusOnState; // whether the stimulus LED is on
	float voltage = 0.0f; // current voltage sent to LED
	Gantry& motors; // reference to class running the motors for the bottom camera
	WindowManager& wnd; // reference to window manager
	ArenaProc* arenaP; // pointer to top camera class
	Config& config; // reference to config file class
	bool gradient; // whether a gradient is being used for the stimulus voltage; constant if false
	bool optoState = false; // used for toggling on and off useOptogenetics bool
	bool useOptogenetics = false; // whether optogenetics is being used in the experiment
	bool constantOn = false; // whether the LED should be manually on
	bool constantOnState = false; // used for setting the bool for turning on the constant light manually
	StimulusType stimType; // which stimulus shape to use
	long long arenaCenter[2]; // center of arena
	double stimulusLineWidth; // width of the rectangle
	double stimulusLineWidthSquared;
	static constexpr long long maxDistanceFromCenter = 260000 / 2; // used to delay pulses or definition of stimulus zone if the fly is too close to the edge of the arena
	static constexpr long long maxDistanceFromCenterSquared = maxDistanceFromCenter * maxDistanceFromCenter;
	unsigned int timer = 0; // running timer for baseline preOpto time period in number of frames
	unsigned int maxTimeMinutes; // starting time of countdown timer in minutes- from config file
	unsigned int numberOfPulses; // number of pulses during automated pulse time- from config file
	unsigned int pulseIntervalLength; // interval between pulses- from config file
	static constexpr double pulseLength = 0.1; // length of each pulse in seconds
	unsigned int maxTimerPart1; // max value for timer variable during preOpto state
	unsigned int maxTimerPart2; // max value for timer variable during automatic pulses
	unsigned int pulseTimer = 0; // timer for each pulse
	unsigned int pulseIntervalTimer = 0; // timer for between pulses
	unsigned int pulseTimerEndValue;
	unsigned int pulseIntervalEndValue;
	ExperimentState experimentState = preOpto; // which part of the experiment it is currently in
	double frequency; // frequency of data collection
	float frequencyFloat; // frequency of data collection
	float pi = static_cast<float>(CV_PI); // pi constant
	long long sumDistanceFromCenterSquared = 0; // for calculating whether the fly is in the stimulus zone circle (x^2+y^2)
	double distanceFromLineSquared = 0; // for calculating whether the fly is in the rectangle zone
	long long distanceFromCircleCenterSquared = 0; // for calculating whether the fly is in the stimulus zone circle
	// used only for old gradient stimulus
	static constexpr float stimulusFrequencyMax = 20.0f; // for old gradient stimulus
	static constexpr float stimulusFrequencyMin = 2.0f; // for old gradient stimulus
	float C;
	//std::mt19937 rng;
	//std::uniform_real_distribution<float> randomNumber;
	//bool randomStimulusTimerRunning = false;
	//std::vector<RandomStimulusTimer> randomStimulusTimers;
	//unsigned int randomStimulusTimerMax;
	// values used when doing experiment with concentric circles with a constant voltage inner circle
	float a;
	float b;
	long long smallerCircleRadius;
	long long smallerCircleRadiusSquared;
	std::mt19937 rng;
	std::uniform_int_distribution<int> offTimeDistribution;
	std::vector<stimulusLineBreak> stimulusLineBreaks;
	static constexpr long long offWidthInCM = 1;
	static constexpr long long offWidthInMicrometers = offWidthInCM * 10000;
	static constexpr long long maxDistanceFromOffLocationSquared = (offWidthInMicrometers / 2) * (offWidthInMicrometers / 2);
	static constexpr int maxTimeBeforeOffSeconds = 5;
	bool discontinuous = false;
};
