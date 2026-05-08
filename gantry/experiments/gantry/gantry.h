#ifndef GANTRY_H
#define GANTRY_H

#include "zaber/motion/ascii.h"
#include "zaber/motion/units.h"
#include <string>
#include <opencv2/opencv.hpp>

using namespace zaber::motion::ascii;
using namespace zaber::motion;

namespace ZaberGantry {

    class Gantry {
    public:

        // replaces the old Gantry function. Requires inputs through the connection since we aren't using analog voltage stuff
        Gantry(const std::string& comPort);

        //inits Zaber devices
        void configure();

        //main function to move, gives a range for how far you want to move relative to current position 
        void SetVelocity(cv::Point2f pt, cv::Point2f vel, bool automatic = true);

    private:

        // stores actuators devices
        std::shared_ptr<Connection> connection;

        //Zaber Axises
        Axis xAxis;
        Axis yAxis;

        // Variables used to keep movement steady
        double kp, kf; // used to make movement more agressive, or slower depending on how far away we are from the fly

        // Velocties to output to the devices
        double velX, velY; 

        //Units
        Units posUnit; // mm
        Units velUnit; // mm/s
        Units accelUnit; // mm/s^2

        // stop flags
        double minLimitX, maxLimitX, minLimitY, maxLimitY;
        double maxSpeed, maxAcceleration;

        // max output we want the velocity to be 
        double maxOutput;

        // Determine the absolute minimum resolvable spot that can be seen on the object
        //objectSpaceResolution = Pixel_Size/PMAG.
        //for more info:https://www.edmundoptics.com/resources/application-notes/imaging/object-space-resolution/
        // objectSpaceResolution is a bottom camera constant used for converting pixels to um micrometers
        // objectSpaceResolution, along with Arena center coordinate are saved to the "*_meta.txt" file output
        double objectSpaceResolution; // 9.6 Neal - This is brought over from the main code to convert pixels to mm
        double mmPerPixel;

        int fps; //T To calculate velocity
    };

} // namespace ZaberGantry

#endif