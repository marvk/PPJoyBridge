#pragma once

#ifdef PPJOYBRIDGE_EXPORTS
#define PPJOYBRIDGE_API __declspec(dllexport)
#else
#define PPJOYBRIDGE_API __declspec(dllimport)
#endif

#include <string>

#include "PPJloctl.h"

#define	NUM_ANALOG	9		/* Number of analog values which we will provide */
#define	NUM_DIGITAL	36		/* Number of digital values which we will provide */

#pragma pack(push,1)		/* All fields in structure must be byte aligned. */
struct JOYSTICK_STATE
{
	unsigned long Signature; /* Signature to identify packet to PPJoy IOCTL */
	char NumAnalog; /* Num of analog values we pass */
	long Analog[NUM_ANALOG]; /* Analog values */
	char NumDigital; /* Num of digital values we pass */
	char Digital[NUM_DIGITAL]; /* Digital values */

	JOYSTICK_STATE()
	{
		Signature = JOYSTICK_STATE_V1;
		NumAnalog = NUM_ANALOG;
		NumDigital = NUM_DIGITAL;
	}

	JOYSTICK_STATE(long analog[], char digital[])
	{
		Signature = JOYSTICK_STATE_V1;
		NumAnalog = NUM_ANALOG;
		NumDigital = NUM_DIGITAL;
		memcpy(Analog, analog, sizeof(Analog));
		memcpy(Digital, digital, sizeof(Digital));
	}
};
#pragma pack(pop)

extern "C" PPJOYBRIDGE_API HANDLE openHandle(const wchar_t* deviceName);
extern "C" PPJOYBRIDGE_API BOOL isHandleValid(HANDLE handle);
extern "C" PPJOYBRIDGE_API DWORD getLastError();
extern "C" PPJOYBRIDGE_API BOOL sendJoystickState(HANDLE handle, long (&analog)[NUM_ANALOG],
                                                  char (&digital)[NUM_DIGITAL]);

extern "C" PPJOYBRIDGE_API long analogMinValue();
extern "C" PPJOYBRIDGE_API long analogMaxValue();

extern "C" PPJOYBRIDGE_API int numberOfAnalogValues();
extern "C" PPJOYBRIDGE_API int numberOfDigitalValues();
