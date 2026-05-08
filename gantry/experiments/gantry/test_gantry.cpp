#include <iostream>
#include <windows.h>
#include "gantry.h"

using namespace ZaberGantry;

int main()
{

    Gantry motors("COM4");
    motors.configure();

    const double manualSpeed = 50.0; // mm per update
    const double manualSpeedy = 50.0; // mm per update

    cv::Point2f virtualDist(0, 0);
    cv::Point2f virtualVel(0, 0);

    while (true)
    {
        virtualDist.x = 0;
        virtualVel.x = 0;
        virtualDist.y = 0;
        virtualVel.y = 0;

        // RIGHT
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
        {
            virtualVel.x = manualSpeed;
            std::cout << "Pressed right\n";
        }



        // LEFT
        if (GetAsyncKeyState(VK_LEFT) & 0x8000)
        {
            virtualVel.x = -manualSpeed;
            std::cout << "Pressed left\n";
        }
        // UP
        if (GetAsyncKeyState(VK_UP) & 0x8000)
        {
            virtualVel.y = manualSpeedy;
            std::cout << "Pressed up\n";
        }



        // DOWN
        if (GetAsyncKeyState(VK_DOWN) & 0x8000)
        {
            virtualVel.y = -manualSpeedy;
            std::cout << "Pressed down\n";
        }

        // ESC to exit
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            break;

        motors.SetVelocity(virtualDist, virtualVel, false);


        Sleep(10);
    }

    std::cout << "Exiting test.\n";
    return 0;
}