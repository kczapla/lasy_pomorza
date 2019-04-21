#pragma once
#include <sstream>
#include <string>

#include "logging_policy.hpp"


namespace logging
{
	struct LoguruLogging : LoggingPolicy<LoguruLogging>
	{
		static void add_file(std::string path);
		static void info(std::ostringstream& msg);
		static void warning(std::ostringstream& msg);
		static void error(std::ostringstream& msg);
	};
}