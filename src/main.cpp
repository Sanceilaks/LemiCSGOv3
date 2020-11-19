#include <iostream>
#include <cstdio>
#include <Windows.h>
#include "hack_core.h"
#include <fstream>
#include <logger.h>
#include <thread>
#include <game_sdk/misc/color.h>
#include "interfaces.h"

HMODULE g_dll;

#define SL_LINK "SL#2200"
#define ZERT_MARK_LINK "ZertMARK#9934"

void init()
{	
	if (!hack_core->init())
		fprintf(stderr, "hack_core::init error!\n");


	//All done message
	interfaces->engine->execute_client_cmd("clear");
	interfaces->cvar->console_color_printf(Color(255, 0, 0), "LemiCSGO is injected!\n\tCreated by:\n");
	interfaces->cvar->console_color_printf(Color(0, 255, 0), "SL %s\t", SL_LINK);
	interfaces->cvar->console_color_printf(Color(0, 0, 255), "ZertMARK %s\n", ZERT_MARK_LINK);
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