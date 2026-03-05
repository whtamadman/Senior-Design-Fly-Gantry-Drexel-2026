//Code used to Test if the devices coming from Zaber have possible issues prior to build
#include <iostream>
#include <vector>
#include <exception>
#include <zaber/motion/ascii.h>

using namespace zaber::motion;
using namespace zaber::motion::ascii;

//Check in the Device Manager for correct COM port number
std::string serial_port = "COM3"; 

int main() {
    try {
        Connection connection = Connection::openSerialPort(serial_port);
        connection.enableAlerts();

        std::vector<Device> deviceList = connection.detectDevices();
        std::cout << "Found " << deviceList.size() << " devices" << std::endl;

        Device device = deviceList[0];

        Axis axis = device.getAxis(1);
        if (!axis.isHomed()) {
            axis.home();
        }

        // Move to 10mm
        //Think that we will most be using this as we have an exact location of points on the gantry
        axis.moveAbsolute(10, Units::LENGTH_MILLIMETRES);

        // Move by an additional 5mm
        //This would be used my Manual control of the gantry
        axis.moveRelative(5, Units::LENGTH_MILLIMETRES);

        return 0;
    } catch (const std::exception& e) {
        // Print the error before crashing the program.
        std::cerr << e.what() << std::endl;
        throw;
    }
}
