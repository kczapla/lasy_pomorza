#include <sstream>

#include "logging.hpp"
#include "logging_loguru.hpp"


namespace logging
{
	using Logging = LoguruLogging;

	void add_file(std::string path)
	{
		Logging::add_file(path);
	}

	Logger::~Logger()
	{
		if (message_level == Level::info) {
			Logging::info(os);
		}
		else if (message_level == Level::warning) {
			Logging::warning(os);
		}
		else if (message_level == Level::error) {
			Logging::error(os);
		}
	}

	std::ostringstream & Logger::get(Level level)
	{
		message_level = level;
		return os;
	}

	void Logger::add_file(std::string path)
	{
		Logging::add_file(path);
	}
}