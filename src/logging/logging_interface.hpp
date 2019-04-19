#pragma once

namespace logging
{
	namespace _logging
	{
		template <typename LoggingImplementation>
		class LoggingInterface
		{
			static void info(std::ostringstream& msg)
			{
				static_cast<LoggingImplementation*>(this)->info(msg);
			}

			static void warning(std::ostringstream& msg)
			{
				static_cast<LoggingImplementation*>(this)->warning(msg);
			}

			static void error(std::ostringstream& msg)
			{
				static_cast<LoggingImplementation*>(this)->error(msg);
			}
		};
	}
}