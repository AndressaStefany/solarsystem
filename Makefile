CC = g++
CXX = g++
CPPFLAGS = -Wall -std=c++11
CFLAGS =
LDFLAGS = -O2 -lGL -lGLU -lglut

FILES = algebra.o texture.o loading.o planet.o camera.o ship.o sky.o interface.o main.o

all: main

main: ${FILES}
	$(CC) $(CFLAGS) ${FILES} $(LDFLAGS) -o $@

main.o: main.cpp

algebra.o: algebra.h algebra.cpp

texture.o: texture.h texture.cpp

loading.o: loading.h loading.cpp

planet.o: planet.h planet.cpp

camera.o: camera.h camera.cpp

ship.o: ship.h ship.cpp

sky.o: sky.h sky.cpp

interface.o: interface.h interface.cpp

##### SPECIAL TARGETS ######

.PHONY: clean realclean

clean:
	-rm -f *.o *~ 

realclean: clean
	-rm -f main

