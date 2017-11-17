CC = g++
CXX = g++
CPPFLAGS = -Wall -std=c++11
CFLAGS =
LDFLAGS = -O2 -lGL -lGLU -lglut

FILES = algebra.o texture.o loading.o planet.o camera.o ship.o sky.o interface.o main.o


all: main

main: ${FILES}
	$(CC) $(CFLAGS) algebra.o texture.o loading.o planet.o camera.o ship.o sky.o interface.o main.o $(LDFLAGS) -o $@

main.o: main.cpp

algebra.o: algebra.h algebra.cpp

texture.o: texture.h texture.cpp

loading.o: loading.h loading.cpp texture.o algebra.o

planet.o: planet.h planet.cpp loading.o

camera.o: camera.h camera.cpp loading.o

ship.o: ship.h ship.cpp loading.o

sky.o: sky.h sky.cpp loading.o

interface.o: interface.h interface.cpp

##### SPECIAL TARGETS ######

.PHONY: clean realclean

clean:
	-rm -f *.o *~ 

realclean: clean
	-rm -f main

