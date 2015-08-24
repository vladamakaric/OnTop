SRC = $(wildcard src/*.cpp)
LIB = -lGL -lGLU -lSDL -lSDLmain -lSDL_gfx -lSDL_image -lSDL_mixer

all: 
	g++ -std=c++11 $(SRC) -o onTop $(LIB) 

clean:
	@echo Cleaning up...
	@rm onTop
	@echo Done.
