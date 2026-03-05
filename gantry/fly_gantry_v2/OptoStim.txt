#include "pch.h"
#include "OptoStim.h"
#include <iostream>
#include <sstream>
#include <string>
#include <Windows.h>

#include <random>
#include <fstream>
#include <math.h>



OptoStim::OptoStim(Gantry& motors_in, double frequency, WindowManager& wnd_in, Config& config_in)
	: motors(motors_in), wnd(wnd_in), config(config_in), frequency(frequency), frequencyFloat(static_cast<float>(frequency))
{
	setConfigParameters();

	std::random_device rd;
	rng = std::mt19937(rd());
	offTimeDistribution = std::uniform_int_distribution<int>((int)frequency, maxTimeBeforeOffSeconds * (int)frequency);
	bool entryReady = true;
	
	
	

	// set parameters based on stimulation type being done in experiment
	switch (stimType)
	{
		//Marcello added 20240618
	case PatternFromFile:
	{
		saveFile.open("OptoPatternFromFile.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string patternFile;
			std::getline(saveFile, patternFile);
			std::ifstream targetFile(patternFile);
			while (std::getline(targetFile, line))
			{
				for (char c : line)
				{
					if (c == '0')
					{
						pattern.push_back(false);
					}
					else if (c == '1')
					{
						pattern.push_back(true);
					}
					else 
					{
						std::cout << "Something went wrong reading the pattern file. Make sure it only has boolean (1 or 0) elements" << std::endl;
					}
				}
			}			
		}
		else
		{
			std::cout << "Could not open OptoPatternFromFile file" << std::endl;
		}
		break;
	}
	case CrudePlume:
	{
		saveFile.open("OptoCrudePlume.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string paramString;
			int n = 0;
			while (std::getline(saveFile, paramString))
			{
				plumePars[n] = std::stoi(paramString);
				n++;
			}
			saveFile.close();
			center[0] = plumePars[0];
			center[1] = plumePars[1];
			plumePars[2] = plumePars[2] * pi / 180;
			plumePars[3] = plumePars[3] * pi / 180;
			slope = tan(plumePars[2]);
			uSlope = tan(plumePars[2] + plumePars[3]);
			lSlope = tan(plumePars[2] - plumePars[3]);
			onPeriod = plumePars[4];
			offPeriod = plumePars[5];
			radSegments = plumePars[6];
			//outFile.open("offTimeCounterDebug.txt");
			//outFile2.open("stimOnStateTimestampDebug.txt");
			//outFile3.open("stimStateBoolDebug.txt");
		}
		else
		{
			std::cout << "Could not open OptoCrudePlume file" << std::endl;
		}
		break;		
	}
	case probPlume:
	{
		saveFile.open("OptoProbPlume.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string paramString;
			int n = 0;
			while (std::getline(saveFile, paramString))
			{
				pPlumePars[n] = std::stof(paramString);
				n++;
			}
			saveFile.close();
			center[0] = pPlumePars[0];
			center[1] = pPlumePars[1];
			
			onPeriod = pPlumePars[2];
			diffusivity = pPlumePars[3];
			slope = pPlumePars[4];
			slope = slope * pi / 180;
			
			
			
			//outFile.open("offTimeCounterDebug.txt");
			//outFile2.open("stimOnStateTimestampDebug.txt");
			//outFile3.open("stimStateBoolDebug.txt");
		}
		else
		{
			std::cout << "Could not open OptoProbPlume file" << std::endl;
		}
		break;
	}
	case CircleStimulus:
	{
		// get saved stimulus location
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

		C = (stimulusFrequencyMin - stimulusFrequencyMax) / static_cast<float>(circleRadius);

		break;
	}
	case LineStimulus:
	{
		// get saved stimulus slope
		saveFile.open("OptoSlope.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
			std::string slopeString;
			int n = 0;
				while (std::getline(saveFile, slopeString))
				{
					slopePars[n] = std::stod(slopeString);
					n++;
				}
			saveFile.close();
			slope = slopePars[0];
			int discontinuousOn = slopePars[1];
			int discontinuousOff = slopePars[2];
		}
		else
		{
			std::cout << "Could not open OptoSlope file" << std::endl;
		}

		C = (stimulusFrequencyMin - stimulusFrequencyMax) / static_cast<float>(stimulusLineWidth / 2);

		break;
	}
	//case WhiteNoiseStimulus added by Marcello
	case WhiteNoiseStimulus:
	{
		saveFile.open("OptoWhiteNoise.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
		std::string paramString;
		int n = 0;
			while (std::getline(saveFile, paramString))
			{
				noiseParams[n] = std::stod(paramString);
				n++;
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open noise OptoWhiteNoise file" << std::endl;
		}
		break;
	}
	//case PulseStimulus added by Marcello
	case PulseStimulus:
	{
		saveFile.open("OptoPulses.txt", std::ios::in);
		std::string line;
		if (saveFile.is_open())
		{
		std::string paramString;
	    int n = 0;
			while (std::getline(saveFile, paramString))
			{
				times[n] = std::stod(paramString);
				n++;
			}
			saveFile.close();
		}
		else
		{
			std::cout << "Could not open noise OptoPulses file" << std::endl;
		}
		break;
	}
	}

	voltageStep = (LED_617_Voltage / rampUpTime) * (1000.0f / 1.0f) * (1.0f / static_cast<float>(frequency));

	maxTimerPart1 = static_cast<unsigned int>(frequency) * maxTimeMinutes * 60;
	maxTimerPart2 = maxTimerPart1 + (numberOfPulses * pulseIntervalLength * static_cast<unsigned int>(frequency)) + static_cast<unsigned int>(pulseLength * frequency) * numberOfPulses;

	pulseTimerEndValue = static_cast<unsigned int>(pulseLength * frequency);
	pulseIntervalEndValue = pulseIntervalLength * static_cast<unsigned int>(frequency);

	a = -LED_617_Voltage / (float)(circleRadius - smallerCircleRadius);
	b = -a * (float)circleRadius;
}


OptoStim::~OptoStim()
{
}

// set whether the stimulus LED should be on based on the encoder position
void OptoStim::setStimulus(long long encoderX, long long encoderY, bool bottomCamFlyFound)
{
	
	// toggle use of optogenetics in the experiment with O key
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

	// start timer and set use of optogenetics to true with T key
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
		// run timer if necessary
		runTimer(encoderX, encoderY, bottomCamFlyFound);

		// set whether to manually turn on and off the LED using P key
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

	bool nonDistanceStimulus = constantOn || experimentState == pulseOn;

	// turn on light if P key is used to turn it on or pulse is happening- not based on fly location
	if (nonDistanceStimulus)
	{
		setOnVoltage(false);
	}
	// set voltage based on fly location if it is inside the stimulus zone
	else if (experimentState == zone && bottomCamFlyFound && isInStimulusZone(encoderX, encoderY,false))
	{
		setOnVoltage(true);
	}
	// otherwise turn off the light
	else
	{
		setOffVoltage();
	}
}

bool OptoStim::getStimulusOnState()
{
	// The commented code here was to debug stimulusOn outlasting specified durations: it comes down to ramp-up time being hardcoded as 100ms.  ramp-up time now specified in
	// gantryConfig.txt
	
	//auto curtim = std::chrono::high_resolution_clock::now();
	//auto dur = curtim.time_since_epoch();
	//auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(dur);
	//outFile2 << ms.count() << endl;
	//outFile3 << stimulusOnState << endl;
	return stimulusOnState;
}

bool OptoStim::usingOptogenetics()
{
	return useOptogenetics;
}

// checks whether the location given is within the stimulus zone
// used for checking whether to turn on the LED
// also used to mark the location in the top camera view
bool OptoStim::isInStimulusZone(long long encoderX, long long encoderY, bool pflag)
{
	if (experimentState != zone)
	{
		return false;
	}

	switch (stimType)
	{
		// true if the fly is in the circle (or larger circle for the concentric case)
		// checks distance from center and whether that is less than the circle radius

	case ConcentricCircleStimulus:
	case CircleStimulus:
	{
		const long long xDistance = center[0] - encoderX;
		const long long yDistance = center[1] - encoderY;

		const long long xDistanceSquared = xDistance * xDistance;
		const long long yDistanceSquared = yDistance * yDistance;

		distanceFromCircleCenterSquared = xDistanceSquared + yDistanceSquared;

		return distanceFromCircleCenterSquared < circleRadiusSquared;
	}
	case probPlume:
	{
		
		xDist = encoderX - pPlumePars[0];
		yDist = encoderY - pPlumePars[1]; //For checking distance from plume source (plumePars[0,1])
		yDist = yDist / 10000;
		xDist = xDist / 10000;

		//double xDistSquared = xDistance * xDistance;
		//double yDistSquared = yDistance * yDistance;
		xDistSquared = xDist * xDist;
		yDistSquared = yDist * yDist;
		distanceFromCircleCenterSquared = xDistSquared + yDistSquared;
		distanceFromCircle = sqrt(distanceFromCircleCenterSquared);
		//Find the greatest distance to the edge of the arena
		distanceToEdge = sqrt((plumePars[0] - (150000 * cos(slope) + 219727)) * (plumePars[0] - (150000 * cos(slope) + 219727)) + (plumePars[1] - (150000 * sin(slope) + 167037)) * (plumePars[1] - (150000 * sin(slope) + 167037)));
		//angDist = abs(atan2(yDist, xDist) - plumePars[2]);

		//############################################################################
		//Used for angled plumes, to be fully implemented later
		// ###########################################################################
		//Rotate the position of the fly so the odor plume is aligned with the positive x axis
		double xrot = xDist * cos(-slope) - yDist * sin(-slope); //downwind distance
		double yrot = xDist * sin(-slope) + yDist * cos(-slope); //signed crosswind distance


		thisOff = 1 / (sqrt(diffusivity * pi * xrot)) * exp(-yrot * yrot / (diffusivity * xrot));
		if (pflag)
		{
			return thisOff > .1;
		}

		std::random_device rd;     // Only used once to initialise (seed) engine
		std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
		std::uniform_real_distribution<float> uniV(0, 1); // Guaranteed unbiased

		proportion = uniV(rng);
		yDist = 0;
		
		
		if (!carrierStimOn && entryReady && proportion < thisOff)
		{
			startCarrierTime = std::chrono::high_resolution_clock::now();
			carrierStimOn = true;
			return true;
		}
		else if (carrierStimOn)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier= std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > onPeriod)
			{
				carrierStimOn = false;
				return false;
			}
			else
			{
				return true;
			}
		}
		else if (!carrierStimOn && entryReady && proportion > thisOff)
		{
			entryReady = false;
			startCarrierTime = std::chrono::high_resolution_clock::now();
			return false;
		}
		else if (!carrierStimOn && !entryReady)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > onPeriod)
			{
				entryReady = true;
			}
			return false;
		}
		return false;
	}
	case CrudePlume:
	{
		xDist = plumePars[0] - encoderX;
		yDist = plumePars[1] - encoderY; //For checking distance from plume source (plumePars[0,1])

		//const long long xDistSquared = xDistance * xDistance;
		//const long long yDistSquared = yDistance * yDistance;
		xDistSquared = xDist * xDist;
		yDistSquared = yDist * yDist;
		distanceFromCircleCenterSquared = xDistSquared + yDistSquared;
		distanceFromCircle = sqrt(distanceFromCircleCenterSquared); 
		//Find the greatest distance to the edge of the arena
		distanceToEdge = sqrt((plumePars[0] - (150000 * cos(slope) + 219727)) * (plumePars[0] - (150000 * cos(slope) + 219727)) + (plumePars[1] - (150000 * sin(slope) + 167037)) * (plumePars[1] - (150000 * sin(slope) + 167037)));



		if (plumePars[2] > 3 * pi / 2 || plumePars[2] < pi / 2)
		{
			//above lower line
			aboveLower = (encoderY > lSlope * (encoderX - plumePars[0]) + plumePars[1]);
			//below upper line
			belowUpper = (encoderY < uSlope * (encoderX - plumePars[0]) + plumePars[1]);
		}
		else  //flip the inequality if in right half of plane
		{
			aboveLower = (encoderY < lSlope * (encoderX - plumePars[0]) + plumePars[1]);
			
			belowUpper = (encoderY > uSlope * (encoderX - plumePars[0]) + plumePars[1]);
		}

		if (pflag)
		{
			return (aboveLower && belowUpper);
		}

		
		if (!carrierStimOn && !carrierStimOff)  //poorly named boolean variables. Using carrierStimOff to determine if we have made our first entry to avoid referencing uninitialized timers
		{
			//empty on purpose, just want to ensure we don't mess with other flags
		}
		else if (!carrierStimOn && !entryReady && !(aboveLower && belowUpper)) //continue the refractory timer outside the triangle
		{
			currentTime = std::chrono::high_resolution_clock::now();  //check if the refractory timer has finished, if so, prepare for next entry
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > offPeriod)
			{
				entryReady = true;
			}
		}
		else if (carrierStimOn && !entryReady && !(aboveLower && belowUpper)) //if we leave during a light pulse, halt pulse immediately and start refractory period
		{
			startCarrierTime = std::chrono::high_resolution_clock::now();
			carrierStimOn = false;
		}
		
		if (!(aboveLower && belowUpper)) //outside of the triangle
		{
			return false;
			
			
		}
		segmentLength = distanceToEdge / radSegments;
		thisSegment = distanceFromCircle / segmentLength;
		proportion = thisSegment / radSegments;
		thisOff = proportion * offPeriod;

		//maybe change this to else if. Currently stops thinking immediately after realizing we are outside the triangle
		if (entryReady) //if after refractory period, start the timer, turn on the stim flag, turn the light on, and turn on refractory period
		{
			startCarrierTime = std::chrono::high_resolution_clock::now();
			carrierStimOff = true; //Poorly named variable, just marks that we have made the first entry so the clock is something we can reference.
			carrierStimOn = true;
			entryReady = false;
			return true;
		}
		else if (carrierStimOn)  //if in the refractory period, check if the light should be on
		{
			currentTime = std::chrono::high_resolution_clock::now();  //if the light should be on, check the current time and compute the duration of the timer
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() < onPeriod) //stay on for the light on duration
			{
				return true;
			}
			else if (elapsedCarrier.count() > onPeriod) // after the light on duration, turn off and start the refractory timer
			{
				startCarrierTime = std::chrono::high_resolution_clock::now();
				carrierStimOn = false;
				return false;
			}
		}
		else if (!carrierStimOn)  //if in the refractory period, check if the light should be off
		{
			currentTime = std::chrono::high_resolution_clock::now(); //check the current time and compute duration
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() < thisOff)  //if we haven't finished the refractory period, keep the light off
			{
				return false;
			}
			else  // if we have finished the refractory period, keep the light off but prepare for reentry
			{
				entryReady = true;
				return false;
			}
		}
		//entryReady = true;
		return false; //if all else fails, turn the light off and prep for next entry
	}
	// gets distance of point to the center line using line slope and point to line distance formula
	// returns true if distance is less than half the width of the line
	case LineStimulus:
	{
		const long long xDistanceFromCenter = encoderX - arenaCenter[0];
		const long long yDistanceFromCenter = encoderY - arenaCenter[1];

		const long long xDistanceFromCenterSquared = xDistanceFromCenter * xDistanceFromCenter;
		const long long yDistanceFromCenterSquared = yDistanceFromCenter * yDistanceFromCenter;
		sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;

		// d = |mx - y| / sqrt(m^2 + 1)
		const double numerator = slope * static_cast<double>(xDistanceFromCenter) - static_cast<double>(yDistanceFromCenter);
		const double numeratorSquared = numerator * numerator;
		const double denominatorSquared = slope * slope + 1.0;
		distanceFromLineSquared = numeratorSquared / denominatorSquared;

		const bool withinBoundary = (distanceFromLineSquared <= stimulusLineWidthSquared / 4) && (sumDistanceFromCenterSquared <= maxDistanceFromCenterSquared);

		
		//bool fe = true;

		if (discontinuous)
		{
			//if (fe)
			//{
			//	startCarrierTime = std::chrono::high_resolution_clock::now();
			//}
			if (withinBoundary && entryReady) //Walked into the light zone and passed a brief rest period
			{
				startCarrierTime = std::chrono::high_resolution_clock::now();  //start the pulse-burst timer, start ignoring the light zone and turn on for the pulse
				carrierStimOn = true;
				entryReady = false;
				return true;
			}
			else if (carrierStimOn)
			{
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
				if (elapsedCarrier.count() < slopePars[1])  //if we haven't finished the pulse, keep the light on
				{
					return true;
				}
				else if (elapsedCarrier.count() > slopePars[3] + slopePars[1] && elapsedCarrier.count() < slopePars[6]) //if we have finished the pulse, wait until we do a short rest and start the burst
				{
					if (!pulseStimOn && !pulseStimOff)		//first part of the burst, start a timer and turn the light off
					{
						startPulseTime = std::chrono::high_resolution_clock::now();
						pulseStimOff = true;
						return false;
					}
					else if (pulseStimOff)  //if we're in the off part of the burst, keep the light off.
					{
						currentTime = std::chrono::high_resolution_clock::now();
						elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
						if (elapsedPulse.count() > slopePars[4]) //If enough time has passed, turn the light on and reset the timer.
						{
							pulseStimOn = true;
							pulseStimOff = false;
							startPulseTime = std::chrono::high_resolution_clock::now();
							return true;
						}
						return false;
					}
					else if (pulseStimOn) //if we're in the on part of the burst, keep the light on
					{
						currentTime = std::chrono::high_resolution_clock::now();
						elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
						if (elapsedPulse.count() > slopePars[5])  //if enough time has passed, turn the light off and reset the timer
						{
							pulseStimOn = false;
							pulseStimOff = true;
							startPulseTime = std::chrono::high_resolution_clock::now();
							return false;
						}
						return true;
					}
					return true;
				}
				else if (elapsedCarrier.count() > slopePars[6]) //if we're done with the pulse-burst cycle, turn the light off and start the long rest timer
				{
					carrierStimOn = false;
					startCarrierTime = std::chrono::high_resolution_clock::now();
					return false;
				}
				return false; //if we're in the short rest, turn the light off

			}
			else if (!carrierStimOn) //if we're out of the long rest, enable light-zone response
			{
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
				pulseStimOff = false;
				pulseStimOn = false;
				if (elapsedCarrier.count() > slopePars[2])
				{
					entryReady = true;
					return false;
				}
				else
				{
					return false;
				}
			}


				//for (std::vector<stimulusLineBreak>::iterator it = stimulusLineBreaks.begin(); it != stimulusLineBreaks.end(); ++it)
				//{
				//	if (it->isWithinOffZone(encoderX, encoderY))
				//	{
				//		return false;
				//	}
				//}
			
		}
		else
		{
			return withinBoundary;
		}
		
	}
	case PatternFromFile:
	{
		if (pflag)
		{
			return false;
		}
		if (!carrierStimOn)
		{
			carrierStimOn = !carrierStimOn;
			startCarrierTime = std::chrono::high_resolution_clock::now();
			
		}
		if (carrierStimOn)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			long long int totalTime = elapsedCarrier.count();
			long long int frameTrigger = static_cast<long long int>(totalTime * (480.0 / 1000.0));

			if (frameTrigger < pattern.size())
			{
				return pattern[frameTrigger];
			}
			else
			{
				return false;
			}
		}
		break;
	}
	case WhiteNoiseStimulus:
	{
		if (pflag)
		{
			return false;
		}
		if (!carrierStimOn && !carrierStimOff)
		{
			carrierStimOff = !carrierStimOff;
			startCarrierTime = std::chrono::high_resolution_clock::now();
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);

		}
		if (carrierStimOn)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > noiseParams[1])
			{
				carrierStimOn = !carrierStimOn;
				carrierStimOff = true;
				pulseStimOn = false;
				startCarrierTime = std::chrono::high_resolution_clock::now();
				
			}
			else if (elapsedPulse.count() > noiseParams[2])
			{
				std::random_device rd;     // Only used once to initialise (seed) engine
				std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
				std::uniform_int_distribution<int> uni(0, 1); // Guaranteed unbiased
				
				
					pulseStimOn = true;
					startPulseTime = std::chrono::high_resolution_clock::now();
				
			}

		}
		else if (carrierStimOff)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > noiseParams[0])
			{
				carrierStimOff = !carrierStimOff;
				carrierStimOn = true;
				startCarrierTime = std::chrono::high_resolution_clock::now();
			}
		}
		return pulseStimOn;
		break;
	}
	case PulseStimulus:
	{
		if (pflag)
		{
			return false;
		}
		if (!carrierStimOff && !carrierStimOn)
		{ 
			carrierStimOff = !carrierStimOff;
			startCarrierTime = std::chrono::high_resolution_clock::now();
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
		}
		if (carrierStimOn)
		{
			
			if (!pulseStimOn && !pulseStimOff)
			{
				//std::chrono::milliseconds duration(times[0]);
				pulseStimOff = !pulseStimOff;
				startPulseTime = std::chrono::high_resolution_clock::now();
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
			}
			if (pulseStimOff)
			{
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
				if (elapsedPulse.count() > times[0])
				{
					pulseStimOn = !pulseStimOn;
					pulseStimOff = !pulseStimOff;
					startPulseTime = std::chrono::high_resolution_clock::now();
				}
			}
			else if (pulseStimOn)
			{
				currentTime = std::chrono::high_resolution_clock::now();
				elapsedPulse = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startPulseTime);
				if (elapsedPulse.count() > times[1])
				{
					pulseStimOn = !pulseStimOn;
					pulseStimOff = !pulseStimOff;
					startPulseTime = std::chrono::high_resolution_clock::now();
				}
			}
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > times[2])
			{
				pulseStimOn = false;
				pulseStimOff = false;
				carrierStimOn = !carrierStimOn;
				startCarrierTime = std::chrono::high_resolution_clock::now();
			}
		}
		else if (carrierStimOff)
		{
			currentTime = std::chrono::high_resolution_clock::now();
			elapsedCarrier = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startCarrierTime);
			if (elapsedCarrier.count() > times[3])
			{
				startCarrierTime = std::chrono::high_resolution_clock::now();
				carrierStimOff = !carrierStimOff;
				carrierStimOn = !carrierStimOn;
			}
		}
		return pulseStimOn;

	}
	}
}

bool OptoStim::isInStimulusZone(float encoderX, float encoderY,bool pflag)
{
	return isInStimulusZone(static_cast<long long>(encoderX), static_cast<long long>(encoderY),pflag);
}

bool OptoStim::isInStimulusZone(int encoderX, int encoderY, bool pflag)
{
	return isInStimulusZone(static_cast<long long>(encoderX), static_cast<long long>(encoderY),pflag);
}

void OptoStim::setArenaCenter(float x, float y)
{
	arenaCenter[0] = static_cast<long long>(x);
	arenaCenter[1] = static_cast<long long>(y);
}

StimulusType OptoStim::getStimulusType()
{
	return stimType;
}

// runs timer for preOpto part of the experiment and pulse part of the experiment
// uses encoder position to decide if a pulse should be given or stimulus zone should be defined
// checks position to see how far from the center the fly is
// if it is too far, it is too close to the edge of the arena to get a pulse or set the stimulus zone
// interval timer for pulses waits at 0 until fly moves from the edge before giving pulse and starting again
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
			sumDistanceFromCenterSquared = xDistanceFromCenterSquared + yDistanceFromCenterSquared;
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

			long long distanceToCheckSquared;
			if (stimType == LineStimulus)
				distanceToCheckSquared = maxDistanceFromCenterSquared;
			else
			{
				const long long distanceToCheck = maxDistanceFromCenter - circleRadius;
				distanceToCheckSquared = distanceToCheck * distanceToCheck;
			}

			if (sumDistanceFromCenterSquared <= distanceToCheckSquared && bottomCamFlyFound)
			{
				if (stimType == LineStimulus)
					setLinearOptoZone(static_cast<float>(encoderX), static_cast<float>(encoderY));
				else
					setCircularOptoZone(static_cast<float>(encoderX), static_cast<float>(encoderY));
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

// get the amount of time left in minutes and seconds and set as string for displaying in top camera view
char* OptoStim::getTimerString()
{
	char timerString[6];
	if (timer < maxTimerPart1 - 1)
	{
		const unsigned int timerInSeconds = timer / static_cast<unsigned int>(frequency);
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

float OptoStim::getStimulusVoltage()
{
	return voltage;
}

long long OptoStim::getSmallerCircleRadius()
{
	return smallerCircleRadius;
}

// get relevant values from config file and calculate and set values
void OptoStim::setConfigParameters()
{
	std::string configStimType = config.getStimulusShape();
	if (configStimType == "rectangle")
		stimType = LineStimulus;
	else if (configStimType == "circle")
		stimType = CircleStimulus;
	else if (configStimType == "concentric circles")
		stimType = ConcentricCircleStimulus;
	else if (configStimType == "pulses")
		stimType = PulseStimulus;
	else if (configStimType == "noise")
		stimType = WhiteNoiseStimulus;
	else if (configStimType == "crudePlume")
		stimType = CrudePlume;
	else if (configStimType == "probPlume")
		stimType = probPlume;
	else if (configStimType == "pattern")
		stimType = PatternFromFile;
	else
	{
		fprintf(stderr, "Invalid stimulus_shape parameter in config file\n");
		exit(EXIT_FAILURE);
	}

	double stimulusLineWidthInCM = config.getRectangleWidth();
	stimulusLineWidth = stimulusLineWidthInCM * 10000;
	stimulusLineWidthSquared = stimulusLineWidth * stimulusLineWidth;

	diameterCM = config.getCircleDiameter();
	circleRadius = (long long)((diameterCM / 2.0f) * 10000.0f);
	circleRadiusSquared = circleRadius * circleRadius;

	if (stimType == ConcentricCircleStimulus)
	{
		const float smallCircleDiameterCM = config.getSmallCircleDiameter();
		smallerCircleRadius = (long long)((smallCircleDiameterCM / 2.0f) * 10000.0f);
		smallerCircleRadiusSquared = smallerCircleRadius * smallerCircleRadius;
	}
	else
	{
		smallerCircleRadius = 0;
		smallerCircleRadiusSquared = 0;
	}

	maxTimeMinutes = config.getBaselineTime();
	numberOfPulses = config.getNumberOfPulses();
	pulseIntervalLength = config.getPulseInterval();

	LED_617_Voltage = config.getVoltage();
	rampUpTime = config.getRamp();

	std::string configStimGradient = config.getStimulusGradient();
	if (configStimGradient == "constant")
		gradient = false;
	else if (configStimGradient == "gradient")
		gradient = true;
	else if (configStimGradient == "discontinuous")
		discontinuous = true;
	else
	{
		fprintf(stderr, "Invalid stimulus_gradient parameter in config file\n");
		exit(EXIT_FAILURE);
	}
}

// set the value of the LED voltage and send it to motors.DriveOptoLED to turn on the light with the calculated voltage
void OptoStim::setOnVoltage(bool distanceBased)
{
	// calculate the voltage to use based on the fly's location within the stimulus zone
	if (distanceBased && gradient && stimType != WhiteNoiseStimulus)
	{
		float distanceToCheck;
		if (stimType == LineStimulus)
			distanceToCheck = static_cast<float>(distanceFromLineSquared);
		else
			distanceToCheck = static_cast<float>(distanceFromCircleCenterSquared);
		voltage = a * sqrtf(distanceToCheck) + b;
		if (voltage > LED_617_Voltage)
			voltage = LED_617_Voltage;
		stimulusOnState = voltage > 0;
		motors.DriveOptoLED(voltage);
	}
	
	// turn on light using ramp up time
	else
	{
		if (stimType == WhiteNoiseStimulus)
		{
			std::random_device rd;     // Only used once to initialise (seed) engine
			std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
			std::uniform_real_distribution<float> uniV(0, LED_617_Voltage); // Guaranteed unbiased

			voltage = uniV(rng);
			stimulusOnState = true;
		}
		else if (voltage < LED_617_Voltage)
		{
			stimulusOnState = true;
			voltage += voltageStep;
		}
		motors.DriveOptoLED(voltage);
	}
}

// ramp down voltage and turn off the light
void OptoStim::setOffVoltage()
{
	//randomStimulusTimers.clear();
	if (voltage > 0)
	{
		voltage -= voltageStep;
		motors.DriveOptoLED(voltage);
	}
	else
	{
		stimulusOnState = false;
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

// set the location of the optogenetics zone circle
void OptoStim::setCircularOptoZone(float x, float y)
{
	center[0] = static_cast<long long>(x);
	center[1] = static_cast<long long>(y);

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

// set the slope of the optogenetics rectangle zone
void OptoStim::setLinearOptoZone(float x, float y)
{
	slope = (static_cast<double>(y) - static_cast<double>(arenaCenter[1])) / (static_cast<double>(x) - static_cast<double>(arenaCenter[0]));
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

// for old way of doing gradient stimulus
//OptoStim::RandomStimulusTimer::RandomStimulusTimer(double frequency)
//{
//	maxRampFrames = static_cast<int>(frequency * static_cast<double>(rampUpTime / 1000.0f));
//}
//
//float OptoStim::RandomStimulusTimer::runTimer(float voltageStep)
//{
//	if (rampUpTimer < maxRampFrames)
//	{
//		rampUpTimer++;
//		randomStimulusTimerVoltage += voltageStep;
//	}
//	else if (rampDownTimer < maxRampFrames)
//	{
//		rampDownTimer++;
//		randomStimulusTimerVoltage -= voltageStep;
//	}
//	else
//	{
//		return -1.0f;
//	}
//	return randomStimulusTimerVoltage;
//}

OptoStim::stimulusLineBreak::stimulusLineBreak(long long x, long long y, int offTimerMax_in, double frequency)
	: offStartLocationX(x), offStartLocationY(y), onTimerMax(offTimerMax_in), offTimeMaxFrames((int)frequency* offTimeMaxSeconds)
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
