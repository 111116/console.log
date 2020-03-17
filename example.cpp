#include "consolelogger.hpp"
#include <cmath>
#include <iomanip>


int main()
{
	console.log("Here prints a log");
	console.info("Here prints an info.");
	console.warn("Here prints a warning!");
	console.error("Here prints an error!!");
	console.debug("This won't be visible if NDEBUG is defined");

	// it's just a wrapper of std::cerr
	std::cerr << std::fixed << std::setprecision(2);
	console.log("PI approx", acos(-1));

	// timer label can be omitted
	console.time("total");
	usleep(123456);
	// use console.timeLog if you don't want to stop the timer
	console.timeEnd("total");
}
