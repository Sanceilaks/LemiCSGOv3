#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "hack_core.h"
#include <fstream>
#include <logger.h>

#include "interfaces.h"

void init()
{	
	if (!hack_core::init())
		fprintf(stderr, "hack_core::init error!\n");

	logger::log("Hello from csgo!");

	char log[240];
	
	sprintf(log, "Engine client %d", reinterpret_cast<int>(interfaces::engine));	
	
	logger::log(log);
}


BOOL APIENTRY DllMain(HMODULE dll, DWORD reason, LPVOID reserved)	//https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain
{	
	DisableThreadLibraryCalls(dll);
	if (reason == DLL_PROCESS_ATTACH)
	{
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), nullptr, 0, 0);
	}
	else if (reason==DLL_PROCESS_DETACH)
	{
		//TO:DO 	
	}
	
	return TRUE;
}