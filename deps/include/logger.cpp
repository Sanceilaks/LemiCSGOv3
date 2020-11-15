#include "logger.h"


#include <fstream>
#include <ostream>
#include <iostream>

std::string log_file = "log.llog";
bool log_in_file = true;

void std_log_func(const std::string& text, logger::log_lvl _log_lvl)
{
	std::cout << logger::log_lvl_text[_log_lvl] << "\t" << text << std::endl;
}

logger::log_func current_log_func = std_log_func;

void logger::set_log_file(const std::string& file)
{
	log_file = file;
}

void logger::log(const std::string& text, log_lvl _log_lvl)
{
	if (log_in_file)
	{
		std::ofstream log(
			log_file, std::ios_base::out | std::ios_base::app);
		log << log_lvl_text[_log_lvl] << "\t" << text << std::endl;
	}
	current_log_func(text, _log_lvl);
}

void logger::set_log_in_file(bool state)
{
	log_in_file = state;
}

void logger::set_log_func(log_func func)
{
	if (func == nullptr)
	{
		current_log_func = std_log_func;
		return;
	}
	current_log_func = func;
}



