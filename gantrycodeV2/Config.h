#pragma once
#include <boost/program_options.hpp>

// uses boost program_options for loading and parsing config file
// check boost documentation
class Config
{
public:
	Config();
	float getVoltage();
	float getRamp();
	double getRectangleWidth();
	float getCircleDiameter();
	unsigned int getBaselineTime();
	unsigned int getNumberOfPulses();
	unsigned int getPulseInterval();
	std::string getStimulusShape();
	std::string getStimulusGradient();
	float getSmallCircleDiameter();
	bool getDebug();
private:
	std::string getConfigFilePath();
	boost::program_options::options_description setOptions();
	void parse_file(std::stringstream& file, boost::program_options::options_description& opts);
private:
	static constexpr char fileName[] = "GantryConfig.txt";
	static constexpr char voltageArgName[] = "voltage";
	static constexpr char rampArgName[] = "ramp";
	static constexpr char rectangleWidthArgName[] = "rectangle_width";
	static constexpr char circleDiameterArgName[] = "circle_diameter";
	static constexpr char baselineTimeArgName[] = "baseline_time";
	static constexpr char numberOfPulsesArgName[] = "pulses";
	static constexpr char pulseIntervalArgName[] = "pulse_interval";
	static constexpr char stimulusShapeArgName[] = "stimulus_shape";
	static constexpr char stimulusGradientArgName[] = "stimulus_gradient";
	static constexpr char smallCircleDiameterArgName[] = "small_circle_diameter";
	static constexpr char debugStimFlag[] = "stim_debug";
	boost::program_options::variables_map vars;
};

