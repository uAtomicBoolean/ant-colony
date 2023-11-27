CC=g++
CFLAGS=-g -Wall -Wextra -ansi -pedantic -std=c++23
CPPFLAGS=-I ./app/include

SOURCES=$(wildcard ./app/*.cpp ./app/src/*.cpp)
EXECUTABLE=./bin/ant_colony


all: create_folders $(EXECUTABLE)


$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@

create_folders:
	mkdir -p ./bin

clean:
	rm -rf $(EXECUTABLE)

doxygen:
	$@ doxyconfig.cfg