CC=g++ -std=c++11
CFLAGS=-c
LDFLAGS= -pthread -lstdc++ 

SOURCES= main.cpp engine/engine.cpp

OBJECTS=$(SOURCES:.cpp=.o)

INCPATH=-Iengine -Imachine

EXE_=themachine

all: $(EXE_)

$(EXE_): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(INCPATH) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE_) $(OBJECTS)

