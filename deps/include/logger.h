/*
	Simple logger by SanceiLaks
	https://github.com/Sanceilaks/simple-logger
	
	@date: 15.11.2020

	TODO: FIX TIME AND FILE LOGGING		(crash game)
*/


#ifndef LLOG
#define LLOG

#include <string>

#ifndef LAPI
#define LAPI
#endif

namespace logger
{
	enum log_lvl
	{
		msg = 0,
		warning,
		error
	};
	/*
	 * For custom
	 * log_lvl_text[log_lvl::msg] = "Custom";
	 */
	static const char* log_lvl_text[] = 
	{
		"[L]",
		"[W]",
		"[E]"
	};
	
	typedef void(*log_func)(const char* text, log_lvl _log_lvl);

	//TODO FIX
	LAPI void init();
	LAPI void set_log_file(const std::string& file);
	LAPI void log(const char* text, log_lvl _log_lvl = msg);
	LAPI void logf(log_lvl _log_lvl, const char* format, ...);
	LAPI void set_log_in_file(bool state);
	LAPI void set_is_log_time(bool state);
	LAPI void set_is_message_box_on_error(bool state);
	LAPI std::string get_current_time();
	/*
	 * Set your own log func. For set std - set_log_func(nullptr);
	 */
	LAPI void set_log_func(log_func func);
	LAPI void set_date_format(const std::string& format);
	LAPI void set_log_in_console(bool state);
	
	LAPI bool get_is_log_time();
	
}

#endif