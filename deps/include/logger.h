/*
	Simple logger by SanceiLaks
	https://github.com/Sanceilaks/simple-logger
	
	@date: 15.11.2020
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

	typedef void(*log_func)(const std::string& text, log_lvl _log_lvl);
	
	LAPI void set_log_file(const std::string& file);
	LAPI void log(const std::string& text, log_lvl _log_lvl = msg);
	LAPI void set_log_in_file(bool state);
	/*
	 * Set your own log func. For set std - set_log_func(nullptr);
	 */
	LAPI void set_log_func(log_func func);
}

#endif