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

MSANFLAGS = -fsanitize=memory
#MSANFLAGS += -fno-omit-frame-pointer
#MSANFLAGS += -fsanitize-memory-use-after-dtor
#MSANFLAGS += -fsanitize-memory-track-origins=2

UBSANFLAGS = -fsanitize=undefined

AFLFLAGS = -Ofast


.PHONY: default
default: build

.PHONY: build
build: src/*.cpp src/*.hpp
	@echo Building
	@#$(CXX) $(DEBUGFLAGS) $(CPPFLAGS) $(OPT) src/*.cpp -o task.out $(LIBS)
	clang++ -g -ggdb -W -Wall -Wextra -Werror src/*.cpp -o task.out -lm

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

.PHONY: analayze
analayze: 
	scan-build -analyze-headers --status-bugs -v -stats make
	


.PHONY: clean
clean:
	@echo Deleting *.out *.o bin textfiles
	-@rm *.out 2>/dev/null || true
	-@rm *.o 2>/dev/null || true

