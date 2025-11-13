CXX := g++
CXXFLAGS := -O2 -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wduplicated-cond -Wlogical-op
TARGET := main
SRC := main.cpp

.PHONY: all build clean test

all: build

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: build
	./test.sh

clean:
	rm -f $(TARGET) tests/*.out.tmp
