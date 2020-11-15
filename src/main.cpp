#include <iostream>
#include <cstdio>
#include <Windows.h>

#include "hack_core.h"


void init()
{
	freopen("C:\\LemiCSGO\\log", "w", stdout);
	
	if (!hack_core::init())
		fprintf(stderr, "hack_core::init error!\n");

	fprintf(stdout, "Hello from csgo stdout!\n");
	std::cout << "Hello from csgo stdout!\n";
}


BOOL WINAPI dll_main(HINSTANCE dll, const DWORD reason, LPVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(dll);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(init), nullptr, 0, 0);
	}
	
	return TRUE;
}