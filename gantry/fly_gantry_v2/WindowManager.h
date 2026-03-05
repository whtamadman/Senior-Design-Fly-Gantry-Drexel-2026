#pragma once

#include <windows.h>
#include <vector>
#include <opencv2/highgui/highgui.hpp>

// used to keep track of gantry program windows so that key presses only work if one of those windows is in focus
class WindowManager
{
public:
	WindowManager();
	~WindowManager();
	bool keyPressed(_In_ int key);
	void newCVWindow(const char* windowName);
private:
	std::vector<HWND> openWindows;
};

