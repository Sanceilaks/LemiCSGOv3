#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "hack_core.h"
#include <fstream>
#include <logger.h>
#include <thread>

#include "interfaces.h"

HMODULE g_dll;


void init()
{
	//logger::init();
	
	using namespace std::chrono_literals;
	if (!hack_core->init())
		fprintf(stderr, "hack_core::init error!\n");

	interfaces->cvar->console_printf("Hello from csgo console! Test int is -> %i", 666);
	
	//FreeLibraryAndExitThread(g_dll, 0);
}


BOOL APIENTRY DllMain(HMODULE dll, DWORD reason, LPVOID reserved)	//https://docs.microsoft.com/en-us/windows/win32/dlls/dllmain
{	
	DisableThreadLibraryCalls(dll);
	if (reason == DLL_PROCESS_ATTACH)
	{
		g_dll = dll;
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), nullptr, 0, 0);
	}
	else if (reason==DLL_PROCESS_DETACH)
	{
		//TODO 	
	}
	
	return TRUE;
}