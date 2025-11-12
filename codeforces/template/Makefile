CXX := g++
CXXFLAGS := -std=c++20 -O2 -pipe -static -s -Wall -Wextra
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
