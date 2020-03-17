#include <cmath>
#include <utility>
#include <vector>
#include <iomanip>
#include "consolelog.hpp"

struct A {
	int x=0, y=0;
};
std::ostream& operator<< (std::ostream& os, const A& a)
{
	return os << '(' << a.x << "," << a.y << ")";
}

// operator<< must be defined in the same namespace as the data structure
namespace std {
	template <typename T1, typename T2>
	std::ostream& operator<< (std::ostream& os, const std::pair<T1,T2>& a)
	{
		return os << '<' << a.first << "," << a.second << ">";
	}

	template <typename T>
	std::ostream& operator<< (std::ostream& os, const std::vector<T>& v)
	{
		os << '[';
		if (!v.empty()) os << v[0];
		for (int i=1; i<v.size(); ++i)
			os << ',' << v[i];
		return os << ']';
	}
}

int main()
{
	// console.loglevel = 3; // error only
	// console.loglevel = 2; // warning & above
	// console.loglevel = 1; // info & above
	// console.loglevel = 0; // logs, timers, counters & above (default)
	console.log("Here prints a log");
	console.info("Here prints an info.");
	console.warn("Here prints a warning!");
	console.error("Here prints an error!!");
	// debugs are not affected by loglevel
	console.debug("This won't be visible if NDEBUG is defined");
	console.log();

	// it's just a wrapper of std::cerr, so you can use iomanip
	std::cerr << std::fixed << std::setprecision(2);
	console.log("PI approx", acos(-1));
	// custom data structures can be used when operator<< is defined
	console.log("a struct", A());
	console.log("a vector", std::vector<int>({1,2,3}));
	console.log("std::pair", std::pair<int,int>(2,3));

	// timer label can be omitted
	console.time("total");
	usleep(123456);
	// use console.timeLog if you don't want to stop the timer
	console.timeEnd("total");

	// counter label can be omitted
	console.count("test");
	// it returns the corresponding count value
	int t = console.count("test");
	console.countReset("test");
}
