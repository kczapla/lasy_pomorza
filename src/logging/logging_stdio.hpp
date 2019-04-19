#pragma once
#include <sstream>
#include <iostream>

#include "logging_interface.hpp"


namespace logging
{
	struct StdIOLogger : _logging::LoggingInterface<StdIOLogger>
	{
		static void add_file(std::string path);
		static void info(std::ostringstream& msg);
		static void warning(std::ostringstream& msg);
		static void error(std::ostringstream& msg);
	};
}