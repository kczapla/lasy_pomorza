#pragma once
#include <string>
#include <sstream>

#define log(level) logging::Logger().get(level)


namespace logging
{
	enum Level
	{
		info, warning, error
	};

	void add_file(std::string);

	class Logger
	{
	public:
		Logger() = default;
		virtual ~Logger();
		std::ostringstream& get(Level level = Level::info);
		void add_file(std::string path);

	private:
		Level message_level = Level::info;
		std::ostringstream os;
	};
} 