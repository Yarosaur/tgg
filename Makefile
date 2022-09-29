BUILD_DIR := ./build

LDFLAGS   := -L/usr/lib/x86-64-linux-gnu
INCLUDES  := -I/usr/include/SFML -Iinclude
LDLIBS    := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXX       := g++
CXXFLAGS  := -std=c++17 -Wall -Wextra
CPPFLAGS  ?= $(INCLUDES) -MMD -MP

OUT       := tgg

SRCS      := $(wildcard ./source/*.cpp)
OBJS      := $(patsubst ./source/%.cpp,./build/%.o,$(SRCS))

MKDIR_P   ?= mkdir -p

all:$(OUT)

$(OUT): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LDLIBS)

./build/%.o: ./source/%.cpp
	$(MKDIR_P) $(@D)	
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -f $(OBJS) $(OUT)
