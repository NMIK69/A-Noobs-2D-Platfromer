CC=g++
CFLAGS=-O0 -Wall -Wextra -std=c++20 -pedantic
LDFLAGS=-lm -lSDL2 -lSDL2_image #-ldl


SRCS=$(wildcard *.cpp ECS/*.cpp ECS/Components/*.cpp ECS/Systems/*.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRCS))

# header dependencies
DEPS=$(wildcard *.h ECS/*.h ECS/Components/*.h ECS/Systems/*.h)


TARGET=game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $< $(LDFLAGS) -o $@


.PHONY : clean
clean :
	rm -f $(TARGET)
	rm -f *.o
	rm -fr ECS/*.o
	rm -fr ECS/Components/*.o
	rm -fr ECS/Systems/*.o

