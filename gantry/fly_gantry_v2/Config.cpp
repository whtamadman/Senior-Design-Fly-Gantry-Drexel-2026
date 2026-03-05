#include "Config.h"
#include <fstream>
#include <iostream>


namespace po = boost::program_options;

Config::Config()
{
	std::stringstream ss;
	std::ifstream configFile(getConfigFilePath());
	if (configFile.fail()) {
		fprintf(stderr, "Could not open configuration file. Check that GantryConfig.txt exists in the users's home folder\n");
		exit(EXIT_FAILURE);
	}
	ss << configFile.rdbuf();
	po::options_description opts = setOptions();
	parse_file(ss, opts);
	configFile.close();
}

std::string Config::getConfigFilePath()
{
	std::string configFilePath = getenv("USERPROFILE") + std::string("\\") + fileName;
	return configFilePath;
}

boost::program_options::options_description Config::setOptions()
{
	po::options_description opts;
	opts.add_options()
		(voltageArgName, po::value<float>())
		(rampArgName, po::value<float>())
		(rectangleWidthArgName, po::value<double>())
		(circleDiameterArgName, po::value<float>())
		(baselineTimeArgName, po::value<unsigned int>())
		(pulseIntervalArgName, po::value<unsigned int>())
		(numberOfPulsesArgName, po::value<unsigned int>())
		(stimulusShapeArgName, po::value<std::string>())
		(stimulusGradientArgName, po::value<std::string>())
		(smallCircleDiameterArgName, po::value<float>())
		(debugStimFlag, po::value<bool>())
		;
	return opts;
}

void Config::parse_file(std::stringstream& file, boost::program_options::options_description& opts)
{
	const bool ALLOW_UNREGISTERED = true;
	po::parsed_options parsed = po::parse_config_file(file, opts, ALLOW_UNREGISTERED);
	po::store(parsed, vars);
	po::notify(vars);
}

float Config::getVoltage()
{
	return vars[voltageArgName].as<float>();
}

//Added by Marcello, subroutine to get user-defined ramp up time.
float Config::getRamp()
{
	return vars[rampArgName].as<float>();
}
double Config::getRectangleWidth()
{
	return vars[rectangleWidthArgName].as<double>();
}

float Config::getCircleDiameter()
{
	return vars[circleDiameterArgName].as<float>();
}

unsigned int Config::getBaselineTime()
{
	return vars[baselineTimeArgName].as<unsigned int>();
}

unsigned int Config::getNumberOfPulses()
{
	return vars[numberOfPulsesArgName].as<unsigned int>();
}

unsigned int Config::getPulseInterval()
{
	return vars[pulseIntervalArgName].as<unsigned int>();
}

std::string Config::getStimulusShape()
{
	return vars[stimulusShapeArgName].as<std::string>();
}

std::string Config::getStimulusGradient()
{
	return vars[stimulusGradientArgName].as<std::string>();
}

float Config::getSmallCircleDiameter()
{
	return vars[smallCircleDiameterArgName].as<float>();
}

bool Config::getDebug()
{
	return vars[debugStimFlag].as<bool>();
}