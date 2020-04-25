
SRC_FILES = $(wildcard *.cpp)
EXE_FILES = $(patsubst %.cpp,%,$(SRC_FILES))

all: $(EXE_FILES)
	@echo "done"

%:%.cpp
	mkdir -p build
	cat common.hpp > build/$<
	cat $< >> build/$<
	cd build; $(CXX) $< -o $@
	cd build; rm $<

