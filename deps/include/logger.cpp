#include "logger.h"


#include <algorithm>
#include <chrono>
#include <stdarg.h>
#include <cstdarg>
#include <fstream>
#include <ostream>
#include <ctime>
#include <windows.h>
#include <shlobj.h>
#include <filesystem>
#include <iostream>

#pragma comment(lib, "shell32.lib")

std::string log_file = "log.llog";
bool log_in_file = false;
bool log_time = false;
bool log_in_console = false;
bool message_box_on_error = true;
std::string time_format = "%hh:%mm:%ss";
//logger::_clog* clog = new logger::_clog();


std::string replace_all(std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	return str;
}

void replace_all(std::string &out, std::string str, const std::string& from, const std::string& to) {
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
	}
	out.swap(str);
}

void std_log_func(const char* text, logger::log_lvl _log_lvl)
{
	if (log_time)
		std::cout << "[" << logger::get_current_time() << "]" << logger::log_lvl_text[_log_lvl] << "\t"  << text << std::endl;
	else
		std::cout << logger::log_lvl_text[_log_lvl] << "\t" << text << std::endl;
}

logger::log_func current_log_func = std_log_func;

void logger::init()
{
	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK)
	{
		throw std::exception("logger::init error!\n");
	}
	
	log_file = std::string(my_documents).append("\\").append(log_file);
}

void logger::set_log_file(const std::string& file)
{
	log_file = file;
}

void logger::log(const char* text, log_lvl _log_lvl)
{
	//if (_log_lvl == error && message_box_on_error)
	//{
	//	auto result = MessageBox(NULL, text, "Error", MB_OK);
	//	
	//	while (result != MB_OK)
	//	{
	//		
	//	}
	//}
	
	if (log_in_file)
	{
		std::ofstream log(
			log_file, std::ios_base::out | std::ios_base::app);
		if (log_time)
			log << "[" << get_current_time() << "]" << log_lvl_text[_log_lvl] << "\t" << text << std::endl;
		else
			log << log_lvl_text[_log_lvl] << "\t" << text << std::endl;

		log.close();
	}
	
	if (log_in_console)
		current_log_func(text, _log_lvl);
}

void logger::logf(log_lvl _log_lvl, const char* fmt, ...)
{	
	va_list ap;
	va_start(ap, fmt);
	char* buf = new char(std::strlen(fmt) * 2);
	vsprintf(buf, fmt, ap);
	va_end(ap);

    log(buf, _log_lvl);
}

void logger::set_log_in_file(bool state)
{
	log_in_file = state;
}

void logger::set_is_log_time(bool state)
{
	log_time = state;
}

void logger::set_is_message_box_on_error(bool state)
{
	message_box_on_error = state;
}

std::string logger::get_current_time()
{
	auto time_point = std::chrono::system_clock::now();
	std::time_t ret_time = std::chrono::system_clock::to_time_t(time_point);

	auto time = ctime(&ret_time);

	auto len_of_new_line = strlen(time) - 1;
	time[len_of_new_line] = '\0';
	
	return std::string(time);

	//time_t theTime = time(NULL);
	//struct tm* aTime = localtime(&theTime);

	//int day = aTime->tm_mday;
	//int month = aTime->tm_mon + 1;
	//int year = aTime->tm_year + 1900;
	//int hour = aTime->tm_hour;
	//int min = aTime->tm_min;
	//int sec = aTime->tm_sec;

	//
	//std::string ret = time_format;
	//replace_all(ret, ret, "%hh", std::to_string(hour));
	//replace_all(ret, ret, "%mm", std::to_string(min));
	//replace_all(ret, ret, "%ss", std::to_string(sec));
	//replace_all(ret, ret, "%YY", std::to_string(year));
	//replace_all(ret, ret, "%MM", std::to_string(month));
	//replace_all(ret, ret, "%DD", std::to_string(day));

	//
	//return ret;
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

void logger::set_date_format(const std::string& format)
{
	time_format = format;
}

void logger::set_log_in_console(bool state)
{
	log_in_console = state;
}

bool logger::get_is_log_time()
{
	return log_time;
}

//void logger::_clog::operator<<(const std::string& text)
//{
//	log(text);
//}
