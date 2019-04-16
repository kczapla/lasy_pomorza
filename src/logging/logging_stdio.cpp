#include <iostream>
#include <sstream>
#include "logging_stdio.hpp"


void logging::StdIOLogger::add_file(std::string path)
{
}

void logging::StdIOLogger::info(std::ostringstream& msg)
{
	std::cout << "[INFO] " << msg.str();
}

void logging::StdIOLogger::warning(std::ostringstream& msg)
{
	std::cout << "[WARNING] " << msg.str();
}

void logging::StdIOLogger::error(std::ostringstream& msg)
{
	std::cout << "[ERROR] " << msg.str();
}