#pragma once
#include <sstream>
#include <iostream>

#include "logging_policy.hpp"


namespace logging
{
	struct StdIOLogger : LoggingPolicy<StdIOLogger>
	{
		static void add_file(std::string path);
		static void info(std::ostringstream& msg);
		static void warning(std::ostringstream& msg);
		static void error(std::ostringstream& msg);
	};
}