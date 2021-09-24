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
#ASANFLAGS += -fno-common
#ASANFLAGS += -fno-omit-frame-pointer
AFLFLAGS = -Ofast


.PHONY: default
default: build

.PHONY: build
build: src/*.cpp src/*.hpp
	@echo Building
	@$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) src/*.cpp -o task.out $(LIBS)
	
.PHONY: better
better: src1/*.cpp src1/*.hpp
	@echo Building
	@#$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) src/*.cpp -o task.out $(LIBS)
	clang++ -g -ggdb -W -Wall -Wextra  src1/*.cpp -o task.out -lm


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
	-@rm curve 2>/dev/null || true

.PHONY obj: curve

liba.o: src/lib.*
	clang++ -c -Wall -Werror -fpic src/lib.cpp -o liba.o
liba.so: liba.o src/lib.hpp
	clang++ -shared -o liba.so liba.o

curve: src/main.cpp liba.so src/lib.hpp
	clang++ -L. -Wl,-rpath=. -Wall -Wextra -Werror -o curve src/main.cpp -la
