CC=g++ -std=c++11
CFLAGS=-c
LDFLAGS= -pthread -lstdc++

SOURCES=state_machine.cpp

OBJECTS=$(SOURCES:.cpp=.o)

EXE_=themachine

all: $(EXE_)

$(EXE_): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE_) $(OBJECTS)

