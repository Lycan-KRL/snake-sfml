INC_DIR = -I../Code/Headers
CFLAGS = -o game -lsfml-graphics -lsfml-window -lsfml-system -Wall $(INC_DIR)

ENGINE = Implementations/Engine.cpp
APPLE = Implementations/Apple.cpp
SNAKE = Implementations/Snake.cpp

OBJECTS = Engine.o Snake.o Apple.o main.o

# Create executable
game: $(OBJECTS)
	@g++ $(OBJECTS) $(CFLAGS)
	@del *.o

# Engine object
Engine.o: $(ENGINE)
	@g++ -c $(ENGINE) $(INC_DIR)

# Snake object
Snake.o: $(SNAKE)
	@g++ -c $(SNAKE) $(INC_DIR)

# Apple object
Apple.o: $(APPLE)
	@g++ -c $(APPLE) $(INC_DIR)

# main Object
main.o: main.cpp
	@g++ -c main.cpp $(INC_DIR)