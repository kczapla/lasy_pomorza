#pragma once
#include <sstream>
#include <string>

#include "logging_loguru.hpp"
#include "logging_stdio.hpp"


#define log(level) logging::Log().get(level)


namespace logging
{
	enum Level
	{
		info, warning, error
	};

	namespace _logging
	{
		template <typename LoggingPolicy>
		void add_file(std::string path)
		{
			LoggingPolicy::add_file(path);
		}

		template <typename LoggingPolicy>
		class Log	
		{
		public:
			Log() = default;
			virtual ~Log();
			std::ostringstream& get(Level level = Level::info);
			void add_file(std::string path);

		private:
			Log(const Log&) = delete;
			Log& operator=(const Log&) = delete;
			Level message_level = Level::info;
			std::ostringstream os;
		};

		template<typename LoggingPolicy>
		inline Log<LoggingPolicy>::~Log()
		{
			if (message_level == Level::info) {
				LoggingPolicy::info(os);
			}
			else if (message_level == Level::warning) {
				LoggingPolicy::warning(os);
			}
			else if (message_level == Level::error) {
				LoggingPolicy::error(os);
			}
		}

		template<typename LoggingPolicy>
		inline std::ostringstream & Log<LoggingPolicy>::get(Level level)
		{
			message_level = level;
			return os;
		}
		template<typename LoggingPolicy>
		inline void Log<LoggingPolicy>::add_file(std::string path)
		{
			LoggingPolicy::add_file(path);
		}
	}

	constexpr auto add_file = _logging::add_file<LoguruLogging>;
	using Log = _logging::Log<LoguruLogging>;
}