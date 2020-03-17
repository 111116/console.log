#include "consolelogger.hpp"
#include <unistd.h>

ConsoleLogger console(std::cerr, isatty(fileno(stderr)));
