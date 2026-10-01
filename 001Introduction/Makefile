# a.cpp -> a.exe (name matches launch.json: fileBasenameNoExtension.exe)
CXX      := g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -g

a.exe: a.cpp
	$(CXX) $(CXXFLAGS) -o $@ a.cpp

clean:
	rm -f a.exe

.PHONY: clean
