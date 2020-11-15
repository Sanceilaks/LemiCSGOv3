#include <iostream>
#include <cstdio>
#include <Windows.h>

#include "hack_core.h"

#include <fstream>

#include <logger.h>


void init()
{
	//freopen("", "w", stdout);
	
	if (!hack_core::init())
		fprintf(stderr, "hack_core::init error!\n");

	logger::log("Hello from csgo!");
}


BOOL APIENTRY DllMain(HMODULE dll, DWORD reason, LPVOID reserved)
{	
	DisableThreadLibraryCalls(dll);
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), nullptr, 0, 0);
	}
	
	return TRUE;
}