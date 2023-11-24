CC=g++
CFLAGS=-g -Wall -Wextra -ansi -pedantic
CPPFLAGS=-I./app/include

SOURCES=$(wildcard ./app/*.cpp ./app/src/*.cpp)
EXECUTABLE=./bin/ant_colony


all: $(EXECUTABLE)


$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(CPPFLAGS) $^ -o $@


clean:
	rm -rf $(EXECUTABLE)
