#pragma once
#include <sstream>


namespace logging
{
	struct StdIOLogger
	{
		static void add_file(std::string path);
		static void info(std::ostringstream&);
		static void warning(std::ostringstream&);
		static void error(std::ostringstream&);
	};
}