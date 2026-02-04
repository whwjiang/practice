CXX ?= g++
CXXSTD ?= c++23
CXXWARN ?= -O2 -Wall -Wextra -Wshadow -Wconversion -Wfloat-equal -Wduplicated-cond -Wlogical-op
CXXFLAGS := -std=$(CXXSTD) $(CXXWARN)

LETTERS := a b c d e f g
PROBLEM ?= a

ifneq (,$(filter $(LETTERS),$(MAKECMDGOALS)))
PROBLEM := $(firstword $(filter $(LETTERS),$(MAKECMDGOALS)))
endif

ifneq (,$(filter test,$(MAKECMDGOALS)))
ifneq (,$(filter $(LETTERS),$(word 2,$(MAKECMDGOALS))))
PROBLEM := $(word 2,$(MAKECMDGOALS))
endif
endif

TARGET := $(PROBLEM).bin
SRC := $(PROBLEM).cpp

all: build

ifneq (,$(filter test,$(MAKECMDGOALS)))
$(LETTERS):
	@:
else
$(LETTERS):
	$(MAKE) build PROBLEM=$@
endif

build:
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

test: build
	./test.sh $(PROBLEM)

clean:
	rm -f $(addsuffix .bin,$(LETTERS)) tests/*/*.out.tmp
