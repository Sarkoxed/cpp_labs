CXX = clang++

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


.PHONY: default
default: build

.PHONY: build
build: src/*.cpp src/*.hpp
	@echo Building
	@$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) src/*.cpp -o task.out $(LIBS)
	
.PHONY: sanitize
sanitize: src/*.cpp src/*.hpp
	@echo Running ASAN
	@$(CXX) $(ASANFLAGS) $(CPPFLAGS) $(DEBUGFLAGS) src/*.cpp -o asan.out $(LIBS)
	@echo "ASAN passed"

asan.out: sanitize

.PHONY: clean
clean:
	@echo Deleting *.out *.o bin textfiles
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm *.so 2>/dev/null || true
	-@rm vector 2>/dev/null || true

.PHONY obj: vect 

liba.o: src/vect.*
	clang++ -c -Wall -Werror -fpic src/vect.cpp -o liba.o
liba.so: liba.o src/vect.hpp
	clang++ -shared -o liba.so liba.o
vect: src/main.cpp liba.so src/vect.hpp
	clang++ -L. -Wl,-rpath=. -Wall -Wextra -Werror -o vector src/main.cpp -la
