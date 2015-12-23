//
// SemaphoreWin.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Nov 18 22:25:17 2015 chapui_s
// Last update Wed Nov 18 22:25:17 2015 chapui_s
//

#include "SemaphoreWin.hh"

SemaphoreWin::SemaphoreWin()
{
	if (!(_sem = CreateSemaphore(nullptr, 0, 1000, nullptr))) {
		DEBUG_MSG("CreateSemaphore() failed");
	}
}

SemaphoreWin::~SemaphoreWin()
{
	if (!CloseHandle(_sem)) {
		DEBUG_MSG("CloseHandle() failed");
	}
}

bool	SemaphoreWin::post()
{
	LONG previousCount;
	if (!(ReleaseSemaphore(_sem, 1, &previousCount))) {
		DEBUG_MSG("ReleaseSemaphore() failed");
		return (false);
	}
	return (true);
}

bool	SemaphoreWin::wait()
{
	//WaitForSingleObject//WaitForMultipleObjects
	if (WaitForSingleObject(_sem, INFINITE) == WAIT_FAILED) {
		return (false);
	}
	return (true);
}

bool	SemaphoreWin::tryWait()
{
	if ((WaitForSingleObject(_sem, 1)) == WAIT_TIMEOUT) {
		return (true);
	}
	return (true);
}
