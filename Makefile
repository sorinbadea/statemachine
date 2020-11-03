CC=g++ -std=c++11
CFLAGS=-c
LDFLAGS= -pthread -lstdc++ 

SOURCES= main.cpp target/test_class.cpp

OBJECTS=$(SOURCES:.cpp=.o)

INCPATH=-Itarget -Imachine

EXE_=themachine

all: $(EXE_)

$(EXE_): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -g -o $@

.cpp.o:
	$(CC) $(INCPATH) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXE_) $(OBJECTS)

