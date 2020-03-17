//
#pragma once

#include <iostream>
#include <string>

class ConsoleLogger
{
private:
	std::ostream& out;

public:
	int errorColor = 31;
	int infoColor = 32;
	int warnColor = 33;

	bool colored = false;
	int loglevel = 0;

	ConsoleLogger(std::ostream&, bool colored);

	// basic logging functions
	template <typename... Args>
	void log(const Args&... args);

	template <typename... Args>
	void info(const Args&... args);

	template <typename... Args>
	void warn(const Args&... args);

	template <typename... Args>
	void error(const Args&... args);

	// timer functions (link consoletimer.cpp if you use these)
	void time(std::string label);
	void timeLog(std::string label);
	void timeEnd(std::string label);

protected:
	void _log();
	template <typename T>
	void _log(const T& t);
	template <typename T, typename... Args>
	void _log(const T& t, const Args&... args);
};

extern ConsoleLogger console;


// ========== Implementation Starts ===========


inline ConsoleLogger::ConsoleLogger(std::ostream& out, bool colored):
	out(out), colored(colored)
{
}


template <typename... Args>
void ConsoleLogger::log(const Args&... args)
{
	_log(args...);
}

template <typename... Args>
void ConsoleLogger::info(const Args&... args)
{
	_log(args...);
}

template <typename... Args>
void ConsoleLogger::warn(const Args&... args)
{
	_log(args...);
}

template <typename... Args>
void ConsoleLogger::error(const Args&... args)
{
	_log(args...);
}


inline void ConsoleLogger::_log()
{
	out << std::endl;
}

template <typename T>
void ConsoleLogger::_log(const T& t)
{
	out << t;
	_log();
}

template <typename T, typename... Args>
void ConsoleLogger::_log(const T& t, const Args&... args)
{
	out << t << " ";
	_log(args...);
}


