#include "consolelogger.hpp"
#include <cmath>
#include <iomanip>


int main() {
	// console.time("total");
	console.log("Here prints a log");
	console.info("Here prints an info.");
	console.warn("Here prints a warning!");
	console.error("Here prints an error!!");
	console.debug("This won't be visible if NDEBUG is defined");
	// it's just a wrapper of std::cerr
	std::cerr << std::fixed << std::setprecision(2);
	console.log("iomanip can be used on std::cerr", acos(-1));
	// timer label defaults to "default" if omitted
	// console.timeLog("total");
	// console.timeEnd("total");
}
