#include "pch.h"
#include "WindowManager.h"
#include <iostream>


WindowManager::WindowManager()
{
	openWindows.push_back(GetConsoleWindow());
}


WindowManager::~WindowManager()
{
}

bool WindowManager::keyPressed(_In_ int key)
{
	if (GetAsyncKeyState(key))
	{
		const HWND focusWindow = GetForegroundWindow();

		for (auto window : openWindows)
		{
			if (focusWindow == window)
			{
				return true;
			}
		}
	}
	return false;
}

void WindowManager::newCVWindow(const char* windowName)
{
	cv::namedWindow(windowName);
	const HWND newWindowHandle = FindWindowA(NULL, windowName);
	openWindows.push_back(newWindowHandle);
	std::cout << "New Window Handle: " << newWindowHandle << std::endl;
}
