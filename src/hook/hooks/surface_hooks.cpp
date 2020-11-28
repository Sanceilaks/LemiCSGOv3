#include "../hooks_manager.h"
#include <features/menu/menu.h>


void hooks::lock_cursor_hook::hook()
{
	if (menu->open)
		interfaces->surface->unlock_cursor();
	else
		original(interfaces->surface);
}
