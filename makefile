CC=g++
CFLAGS=-g -Wall -Wextra -ansi -pedantic -std=c++11 -lsfml-graphics -lsfml-window -lsfml-system
CPPFLAGS=-I ./app/include

SRC=./app/src
SOURCES=$(wildcard ./app/*.cpp $(SRC)/*.cpp $(SRC)/model/colonie/*.cpp $(SRC)/model/colonie/fourmi/*.cpp)
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