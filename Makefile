CC = g++ -std=c++11 -g -Wall
exe_file = zoo_tycoon
$(exe_file): animal.o seaLion.o zoo.o bear.o tiger.o util.o prog.o 
	$(CC) animal.o seaLion.o zoo.o util.o bear.o tiger.o prog.o -o $(exe_file)
animal.o: animal.cpp
	$(CC) -c animal.cpp
seaLion.o: seaLion.cpp
	$(CC) -c seaLion.cpp
zoo.o: zoo.cpp
	$(CC) -c zoo.cpp
util.o: util.cpp
	$(CC) -c util.cpp
bear.o: bear.cpp
	$(CC) -c bear.cpp
tiger.o: tiger.cpp
	$(CC) -c tiger.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp

clean:
	rm *.o $(exe_file)

tar:
	tar -cvf $(exe_file).tar *.cpp *.h Makefile
