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

COVFLAGS = -fprofile-arcs
COVFLAGS += -ftest-coverage

SOURCE_DIR = src
LIBRARY_DIR = lib
PROJECT_NAME = project
LIBRARY_NAME = table

.PHONY: default
default: build

.PHONY: build
build: $(SOURCE_DIR)/* $(LIBRARY_DIR)/*
	@echo Building
	@$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) $(SOURCE_DIR)/*.cpp $(LIBRARY_DIR)/*.cpp -o build.out $(LIBS)
	
.PHONY: sanitize
sanitize: $(SOURCE_DIR)/* $(LIBRARY_DIR)/*
	@echo Building
	@$(CXX) $(ASANFLAGS) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) $(SOURCE_DIR)/*.cpp $(LIBRARY_DIR)/*.cpp -o asan.out $(LIBS)
	@echo "ASAN passed"

asan.out: sanitize


.PHONY: project
project: lib$(LIBRARY_NAME).so $(SOURCE_DIR)/*.cpp
	@echo "Building project"
	@$(CXX) -L. -Wl,-rpath=. $(CPPFLAGS) -o $(PROJECT_NAME) $(SOURCE_DIR)/*.cpp -l$(LIBRARY_NAME)

.PHONY: object
object: lib$(LIBRARY_NAME).so

lib$(LIBRARY_NAME).o: $(LIBRARY_DIR)/*.cpp
	@$(CXX) -c -Wall -fpic $(LIBRARY_DIR)/*.cpp -o lib$(LIBRARY_NAME).o

lib$(LIBRARY_NAME).so: lib$(LIBRARY_NAME).o $(LIBRARY_DIR)/*.cpp
	@$(CXX) -shared -o lib$(LIBRARY_NAME).so lib$(LIBRARY_NAME).o


.PHONY: clean
clean:
	@echo Deleting *.out *.o bin textfiles
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true
	-@rm *.so 2>/dev/null || true
	-@rm $(PROJECT_NAME) 2>/dev/null || true

