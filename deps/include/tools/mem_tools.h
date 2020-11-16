#pragma once
#include <cstdint>

namespace mem_tools
{
	void* capture_interface(const char* _module, const char* _interface);
	uint8_t* patternt_scanner(const char* module_name, const char* signature) noexcept;
}
