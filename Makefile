all: example example_advanced *.hpp *.cpp

example: consolelog.hpp example.cpp Makefile
	g++ -std=c++11 example.cpp -o example

example_advanced: consolelog.hpp example_advanced.cpp aux.cpp Makefile
	g++ -std=c++11 aux.cpp example_advanced.cpp -o example_advanced
