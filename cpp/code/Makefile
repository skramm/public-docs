
SRC_FILES = $(wildcard *.cpp)
EXE_FILES = $(patsubst %.cpp,build/%,$(SRC_FILES))

CFLAGS+=-std=c++11

all: $(EXE_FILES)
	@echo "done"

build/%.cpp:%.cpp
	mkdir -p build
	cat common.hpp > $@
	cat $< >> $@

build/%:build/%.cpp
	$(CXX) $(CFLAGS) $< -o $@
#	cd build; rm $<

