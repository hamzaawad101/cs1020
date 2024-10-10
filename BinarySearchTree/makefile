# Project: BinarySearchTree

CPP      = g++
OBJ      = main.o activity.o participant.o
LINKOBJ  = main.o activity.o participant.o
LIBS     = # (You can remove Windows-specific library paths if not needed on macOS)
INCS     = # (You can remove Windows-specific include paths if not needed on macOS)
BIN      = a.out   # No .exe extension for macOS
CXXFLAGS = $(INCS)
DEL      = rm -f

.PHONY: all clean run

all: $(BIN)

clean:
	$(DEL) $(OBJ) $(BIN)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)

main.o: main.cpp
	$(CPP) -c main.cpp -o main.o $(CXXFLAGS)

activity.o: activity.cpp
	$(CPP) -c activity.cpp -o activity.o $(CXXFLAGS)

participant.o: participant.cpp
	$(CPP) -c participant.cpp -o participant.o $(CXXFLAGS)

run: $(BIN)
	./$(BIN)    # Running the binary directly
