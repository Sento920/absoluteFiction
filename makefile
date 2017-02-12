
CPP = g++
CFLAGS = -Wall -Werror -g -std=c++11 -pedantic
LIBS = 
TARGET = abfic

#paths for src files and obj files separated
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, obj/%.o, $(SRC))


all: $(TARGET)

$(TARGET): $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS) $(LIBS)

obj/%.o: src/%.cpp 
	$(CPP) $(CFLAGS) -c -o $@ $< $(LIBS)
	
obj/%.o: src/%.cpp src/%.h 
	$(CPP) $(CFLAGS) -c -o $@ $< $(LIBS)

clean:
	rm -f obj/*.o $(TARGET)
