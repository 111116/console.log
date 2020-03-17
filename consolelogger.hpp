// console.log: Javascript-styled console logger for C++
#pragma once

#include <iostream>
#include <unistd.h> // isatty
#include <unordered_map> // label-time pairs
#include <string> // labels
#include <chrono> // time
#include <cmath>

namespace github111116 {
class ConsoleLogger
{
protected:
	std::ostream& out;

public:
	std::string  infoColor = "\033[0;32m";
	std::string  warnColor = "\033[1;33m";
	std::string errorColor = "\033[1;31m";
	bool colored = false;
	int loglevel = 0;

	ConsoleLogger(std::ostream& out, bool colored);
	// basic logging functions
	template <typename... Args> void log(const Args&... args); // loglevel:0
	template <typename... Args> void info(const Args&... args); // loglevel:1
	template <typename... Args> void warn(const Args&... args); // loglevel:2
	template <typename... Args> void error(const Args&... args); // loglevel:3
	template <typename... Args> void debug(const Args&... args); // only affected by NDEBUG flag
	// timer functions
	void time(const std::string& label = "default");
	void timeLog(const std::string& label = "default");
	void timeEnd(const std::string& label = "default");

protected:
	void print();
	template <typename T>
	void print(const T& t);
	template <typename T, typename... Args>
	void print(const T& t, const Args&... args);
	std::unordered_map<std::string, std::chrono::time_point<std::chrono::system_clock>> starttimes;
};
}


// defining global variable "console"
__attribute__((weak)) github111116::ConsoleLogger console(std::cerr, isatty(fileno(stderr)));



// ========== Implementation Starts ===========

namespace github111116 {

inline ConsoleLogger::ConsoleLogger(std::ostream& out, bool colored):
	out(out), colored(colored)
{
}

template <typename... Args>
void ConsoleLogger::log(const Args&... args)
{
	if (loglevel > 0) return;
	out << "    ";
	print(args...);
}

template <typename... Args>
void ConsoleLogger::debug(const Args&... args)
{
#ifndef NDEBUG
	out << "... ";
	print(args...);
#endif
}

template <typename... Args>
void ConsoleLogger::info(const Args&... args)
{
	if (loglevel > 1) return;
	if (colored) out << infoColor;
	out << "[i] ";
	if (colored) out << "\033[0m";
	print(args...);
}

template <typename... Args>
void ConsoleLogger::warn(const Args&... args)
{
	if (loglevel > 2) return;
	if (colored) out << warnColor;
	out << "[!] ";
	print(args...);
	if (colored) out << "\033[0m";
}

template <typename... Args>
void ConsoleLogger::error(const Args&... args)
{
	if (loglevel > 3) return;
	if (colored) out << errorColor;
	out << "[X] ";
	print(args...);
	if (colored) out << "\033[0m";
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

inline void ConsoleLogger::time(const std::string& label)
{
	if (starttimes.count(label))
	{
		warn("Timer \"" + label + "\" already exists.");
		return;
	}
	starttimes[label] = std::chrono::system_clock::now();
}

inline void ConsoleLogger::timeLog(const std::string& label)
{
	if (!starttimes.count(label))
	{
		warn("Timer \"" + label + "\" doesn't exist.");
		return;
	}
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = now - starttimes[label];
	out << "    "+label+": " << (long long)(seconds.count()*1000)/1000 << "s" << std::endl;
}

inline void ConsoleLogger::timeEnd(const std::string& label)
{
	if (!starttimes.count(label))
	{
		warn("Timer \"" + label + "\" doesn't exist.");
		return;
	}
	auto now = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = now - starttimes[label];
	out << "    "+label+": " << 0.001*round(seconds.count()*1000) << "s - timer ended" << std::endl;
	starttimes.erase(label);
}

} // end namespace
