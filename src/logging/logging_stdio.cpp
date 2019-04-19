#include "logging_stdio.hpp"


namespace logging
{
    void StdIOLogger::add_file(std::string path)
    {

    }

    void StdIOLogger::info(std::ostringstream& msg)
    {
        std::cout << "[INFO] " << msg.str();
    }

    void StdIOLogger::warning(std::ostringstream& msg)
    {
        std::cout << "[WARNING] " << msg.str();
    }

    void StdIOLogger::error(std::ostringstream& msg)
    {
        std::cout << "[ERROR] " << msg.str();
    }
}