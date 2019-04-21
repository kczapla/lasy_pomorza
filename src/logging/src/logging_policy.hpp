#include <string>


namespace logging
{
    template <typename LoggingImplementation>
    struct LoggingPolicy
    {
        static void add_file(std::string);
        static void info(std::string);
        static void warning(std::string);
        static void error(std::string);
    };
	
	template<typename LoggingImplementation>
	inline void LoggingPolicy<LoggingImplementation>::add_file(std::string path)
	{
		static_cast<LoggingImplementation*>(this)->add_file(path);
	}
	
	template<typename LoggingImplementation>
	inline void LoggingPolicy<LoggingImplementation>::info(std::string msg)
	{
		static_cast<LoggingImplementation*>(this)->info(msg);
	}
	
	template<typename LoggingImplementation>
	inline void LoggingPolicy<LoggingImplementation>::warning(std::string msg)
	{
		static_cast<LoggingImplementation*>(this)->warning(msg);
	}
	
	template<typename LoggingImplementation>
	inline void LoggingPolicy<LoggingImplementation>::error(std::string msg)
	{
		static_cast<LoggingImplementation*>(this)->error(msg);
	}
}