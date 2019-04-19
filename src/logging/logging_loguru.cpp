#define LOGURU_WITH_STREAMS 1
#include <loguru.cpp>
#include "logging_loguru.hpp"


void logging::LoguruLogging::add_file(std::string path)
{
	loguru::add_file(path.c_str(), loguru::Truncate, loguru::Verbosity_MAX);
}

void logging::LoguruLogging::info(std::ostringstream & msg)
{
	LOG_S(INFO) << msg.str();
}

void logging::LoguruLogging::warning(std::ostringstream & msg)
{
	LOG_S(WARNING) << msg.str();
}

void logging::LoguruLogging::error(std::ostringstream & msg)
{
	LOG_S(ERROR) << msg.str();
}
