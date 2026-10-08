CXX ?= g++

CXXFLAGS += -c -Wall `pkg-config --cflags opencv4`
LDFLAGS += `pkg-config --libs opencv4`

LAB = #EL
NUM = #00

#The task is only relevant for the Code::Blocks targets Debug and Release.
#Change it if you want to build and debug/run a different task within Code::Blocks.
TASK = a b

SRC = $(wildcard *.cpp)
EXE = $(addprefix $(LAB)$(NUM), $(SRC:.cpp=.exe))

all: $(EXE)

Debug: CXXFLAGS += -g
Debug: $(LAB)$(NUM)$(TASK).exe

Release: $(LAB)$(NUM)$(TASK).exe

$(LAB)$(NUM)%.exe: %.o
	$(CXX) $< -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(EXE)
