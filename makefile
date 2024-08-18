# Makefile

# Compiler options
CXX = gcc
CXXFLAGS = -std=c11 -Wall -g -I ./include
CXXFAST = -Ofast -finline-functions -ftree-loop-optimize
# Source files
SRCS := $(wildcard ./src/*.c)

# Object files
OBJS := $(patsubst ./src/%.c,./obj/%.o,$(SRCS))

# Target executable
TARGET := ./bin/tp3.out 

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lm

./obj/%.o: ./src/%.c
	$(CXX) $(CXXFLAGS) -c $< -o $@ -lm

clean:
	rm -f $(OBJS) $(TARGET)
