
CPP = g++
CFLAGS = -Wall -g -std=c++11 -pedantic
LIBS = 
TARGET = Bleak

SRC = $(wildcard ./*.cpp)
OBJ = $(patsubst ./%.cpp,./%.o, $(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) $(LIBS)

%.o: %.cpp 
	$(CPP) $(CFLAGS) -c -o $@ $< 
	
%.o: %.cpp %.h 
	$(CPP) $(CFLAGS) -c -o $@ $<

clean:
	rm -f *.o $(TARGET)
