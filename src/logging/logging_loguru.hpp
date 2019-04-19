#pragma once
#include <sstream>

#include "logging_interface.hpp"


namespace logging
{
	struct LoguruLogging : _logging::LoggingInterface<LoguruLogging>
	{
		static void add_file(std::string path);
		
		static void info(std::ostringstream& msg);

		static void warning(std::ostringstream& msg);

		static void error(std::ostringstream& msg);
	};
}