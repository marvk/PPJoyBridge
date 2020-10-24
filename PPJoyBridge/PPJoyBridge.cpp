#include "pch.h"
#include "PPJoyBridge.h"

#include <iostream>
#include <conio.h>
#include <fstream>
#include <Windows.h>
#include <winioctl.h>

HANDLE openHandle(const wchar_t* deviceName)
{
	return CreateFile(deviceName, GENERIC_WRITE, FILE_SHARE_WRITE, nullptr, OPEN_EXISTING, 0, nullptr);
}

BOOL isHandleValid(HANDLE handle)
{
	return handle != INVALID_HANDLE_VALUE;
}

DWORD getLastError()
{
	return GetLastError();
}

BOOL sendJoystickState(HANDLE handle, long (&analog)[NUM_ANALOG], char (&digital)[NUM_DIGITAL])
{
	JOYSTICK_STATE joyState(analog, digital);
	DWORD retSize;

	return DeviceIoControl(handle, IOCTL_PPORTJOY_SET_STATE, &joyState, sizeof(joyState), nullptr, 0, &retSize,
	                       nullptr);
}

long analogMinValue()
{
	return 1;
}


long analogMaxValue()
{
	return 32767;
}

int numberOfAnalogValues()
{
	return NUM_ANALOG;
}


int numberOfDigitalValues()
{
	return NUM_DIGITAL;
}