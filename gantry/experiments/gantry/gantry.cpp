#include "gantry.h"
#include <iostream>

using namespace zaber::motion::ascii;
using namespace zaber::motion;

namespace ZaberGantry {

    ZaberGantry::Gantry::Gantry(const std::string& comPort) {

        // Open COM port and get zaber controller
        connection = std::make_shared<Connection>(Connection::openSerialPort(comPort));

        // Grab controller
        auto connectionDevice = connection->detectDevices();
        auto device = std::make_shared<Device>(connectionDevice.at(0));

        // Grab axises connected to controller
        xAxis = device->getAxis(2);
        yAxis = device->getAxis(1);

        //Init vars
        velUnit = Units::VELOCITY_MILLIMETRES_PER_SECOND;
        accelUnit = Units::ACCELERATION_MILLIMETRES_PER_SECOND_SQUARED;
        posUnit = Units::LENGTH_MILLIMETRES;
        velX = 0; velY = 0;
        kp = 40.0f; kf = 0.0f;
        objectSpaceResolution = (4.8 / 0.5)/1000.0; // pixel to mm
        minLimitX = 0; minLimitY = 0; maxLimitX = 1000; maxLimitY = 600; //Max limit thresholds for how far the actuator can move
        maxSpeed = 90.0; maxAcceleration = 1000.0; // Max limit for velocity and acceleration mm/s and mm/s^2
        fps = 480; // To calculate actual velocity

        std::cout << "Found port and set axes.\n";
    }

    void Gantry::configure()
    {


        xAxis.getSettings().set("maxspeed", maxSpeed, velUnit);
        yAxis.getSettings().set("maxspeed", maxSpeed, velUnit);

        xAxis.getSettings().set("limit.min", minLimitX, posUnit);
        xAxis.getSettings().set("limit.max", maxLimitX, posUnit);

        yAxis.getSettings().set("limit.min", minLimitY, posUnit);
        yAxis.getSettings().set("limit.max", maxLimitY, posUnit);

        Axis::MoveVelocityOptions options;
        options.acceleration = maxAcceleration;
        options.accelerationUnit = accelUnit;

        std::cout << "Zaber axes configured and homed with velocity and acceleration options.\n";

    }

    // Main control loop (replacement for SetDirAndFreq)
    void Gantry::SetVelocity(cv::Point2f pt, cv::Point2f vel, bool automatic)
    {

        //May need to use this code if camera fps does not work, if I do then, divide by dt rather than multiply by fps
        // static auto last = std::chrono::high_resolution_clock::now();

        // auto now = std::chrono::high_resolution_clock::now();
        // double dt = std::chrono::duration<double>(now - last).count();
        // last = now;

        // reset velocities
        velX = 0; velY = 0;
        
        //convert pixels to mm
        
        if (automatic) {
            double ptInMMx, ptInMMy, velInMMx, velInMMy;
            ptInMMx = pt.x * objectSpaceResolution;
            ptInMMy = pt.y * objectSpaceResolution;
            velInMMx = vel.x * objectSpaceResolution * fps;
            velInMMy = vel.y * objectSpaceResolution * fps;
            // iErrorX += errorX; Neal - No longer needed snce Zaber has smooth enough movement
            // iErrorY += errorY;
            velX = kp * ptInMMx + kf * velInMMx;
            velY = kp * ptInMMy + kf * velInMMy;
        }
        else {
            velX = vel.x;
            velY = vel.y;
        }

        // Clamp output to maxOutput speed
        if (velX > maxOutput) velX = maxSpeed;
        if (velX < -maxOutput) velX = -maxSpeed;
        if (velY > maxOutput) velY = maxSpeed;
        if (velY < -maxOutput) velY = -maxSpeed;

        double posX = xAxis.getPosition(posUnit);
        double posY = yAxis.getPosition(posUnit);

        // Safety checks to make sure if we are past the bounds, that we dont go further
        if ((posX >= maxLimitX  && velX >= 0) || (posX <= minLimitX && velX <= 0))
            velX = 0;

        if ((posY >= maxLimitY && velY >= 0) || (posY <= minLimitY && velY <= 0))
            velY = 0;

        // Try to move otherwise, throw error if u can't
        try {
            xAxis.moveVelocity(velX, velUnit);
            yAxis.moveVelocity(velY, velUnit);
        }
        catch (const std::exception& e) {
            std::cerr << "Motion error: " << e.what() << std::endl;
        }
    }
} // namespace ZaberGantry