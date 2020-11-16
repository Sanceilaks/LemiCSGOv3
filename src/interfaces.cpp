#include "interfaces.h"
#include <tools/mem_tools.h>

IVEngineClient* interfaces::engine;


void interfaces::init()
{
	engine = static_cast<IVEngineClient*>(mem_tools::capture_interface("engine.dll", "VEngineClient014"));
	
}


void interfaces::print_interfaces()
{

}