CXX = clang++
#CXX = g++
#OPT = -O3

LIBS = -lm

CPPFLAGS = -Wall
#CFLAGS += -Wfloat-equal
CPPFLAGS += -Wextra
CPPFLAGS += -pedantic
#CPPFLAGS += -Werror
#CPPFLAGS += -Wmissing-declarations
#CPPFLAGS += -fstack-protector-all

DEBUGFLAGS = -g
DEBUGFLAGS += -ggdb

ASANFLAGS = -fsanitize=address
AFLFLAGS = -Ofast

SFML_DIR=../SFML
SFML_INCL=../SFML/include

SRC_DIR=src
TOOLS=tools

#SRC = $(SRC_DIR)/**/*.cpp tools/toolib.cpp
SRC = src/game/*.cpp
game.o: $(SRC) 
	clang++ -c $(SRC) -I $(SFML_INCL)

game.out: game.o
	clang++ game.o -o game.out -L $(SFML_DIR)/lib -Wl,-rpath $(SFML_DIR)/lib -lsfml-graphics -lsfml-window -lsfml-system


test.out: lol.cpp src/items/*.cpp src/level/*.cpp src/character/*.cpp src/inventory/*.cpp tools/toolib.cpp
	clang++ $^ -g -ggdb -fsanitize=address -o test.out

.PHONY: clean
clean:
	rm *.o  || true 
	rm *.a  || true 
	rm *.out || true
	rm src/**/*.gch

