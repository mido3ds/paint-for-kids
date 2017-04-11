# directories
SRC_DIR = {**,.}

BLD_DIR = Build

# executable
EXEC = $(BLD_DIR)/main

# compiler, use compiler for windows
COMPILER = i586-mingw32-g++

CPP_VER = 11

COMPILER_FLAGS = -std=c++$(CPP_VER)
COMPILER_FLAGS += -I GUI -I CMUgraphicsLib -I CMUgraphicsLib/jpeg
COMPILER_FLAGS += -g
COMPILER_FLAGS += $(SRC_DIR)/*.cpp CMUgraphicsLib/jpeg/*.c CMUgraphicsLib/*.c -c 

syntax:
	$(COMPILER) -fsyntax-only {GUI,Figures,.}/*.{cpp,h}

compile: 
	$(COMPILER) $(COMPILER_FLAGS) && $(COMPILER) *.o
	make clean

duty:
	egrep -H -n '(BUG|TODO):' **/* ** * -A 1 -B 1 2> /dev/null

format:
	clang-format -sort-includes -style=WebKit -i {GUI,Figures,Actions,.}/*.{cpp,h}

update:
	git add .; git commit && git push || echo aborted

clean:
	rm -rf $(EXEC) 2> /dev/null
	rm -rf *.o *.dSYM $(BLD_DIR)/*.dSYM 2> /dev/null