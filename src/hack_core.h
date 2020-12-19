#pragma once
#include <Windows.h>

class HackCore
{
public:
	bool init();
	void destroy();

	HMODULE dll;
}; extern HackCore* hack_core;
