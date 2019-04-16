#define LOGURU_WITH_STREAMS 1
#include <loguru.cpp>

#include "logging_loguru.hpp"


void logging::LoguruLogger::add_file(std::string path)
{
	loguru::add_file(path.c_str(), loguru::Truncate, loguru::Verbosity_MAX);
}

void logging::LoguruLogger::info(std::ostringstream& msg)
{
	LOG_S(INFO) << msg.str();
}

void logging::LoguruLogger::warning(std::ostringstream& msg)
{
	LOG_S(WARNING) << msg.str();
}

void logging::LoguruLogger::error(std::ostringstream& msg)
{
	LOG_S(ERROR) << msg.str();
}