// console.log: Javascript-styled console logger for C++
#pragma once

#include <iostream>
#include <unordered_map>
#include <string>
#include <unistd.h>


class ConsoleLogger
{
private:
	std::ostream& out;

public:
	int errorColor = 31;
	int  infoColor = 32;
	int  warnColor = 33;
	int loglevel = 0;
	bool colored = false;

	ConsoleLogger(std::ostream& out, bool colored);
	// basic logging functions
	template <typename... Args> void log(const Args&... args);
	template <typename... Args> void info(const Args&... args);
	template <typename... Args> void warn(const Args&... args);
	template <typename... Args> void error(const Args&... args);
	// timer functions (link consoletimer.cpp if you use these)
	void time(std::string label = "default");
	void timeLog(std::string label = "default");
	void timeEnd(std::string label = "default");

protected:
	void print();
	template <typename T>
	void print(const T& t);
	template <typename T, typename... Args>
	void print(const T& t, const Args&... args);
	std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> starttimes;
};

__attribute__((weak)) ConsoleLogger console(std::cerr, isatty(fileno(stderr)));


// ========== Implementation Starts ===========

inline ConsoleLogger::ConsoleLogger(std::ostream& out, bool colored):
	out(out), colored(colored)
{

}

template <typename... Args>
void ConsoleLogger::log(const Args&... args)
{
	print(args...);
}

template <typename... Args>
void ConsoleLogger::info(const Args&... args)
{
	print(args...);
}

template <typename... Args>
void ConsoleLogger::warn(const Args&... args)
{
	print(args...);
}

template <typename... Args>
void ConsoleLogger::error(const Args&... args)
{
	print(args...);
}


inline void ConsoleLogger::print()
{
	out << std::endl;
}

template <typename T>
void ConsoleLogger::print(const T& t)
{
	out << t;
	print();
}

template <typename T, typename... Args>
void ConsoleLogger::print(const T& t, const Args&... args)
{
	out << t << " ";
	print(args...);
}


