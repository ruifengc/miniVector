objects = minimemory/minimemory.o miniVector/miniVector.o
miniVector.out:${objects}
	g++ ${objects} -o miniVector.out
minimemory/minimemory.o:minimemory/minimemory.cpp minimemory/minimemory.h
	g++ -c minimemory/minimemory.cpp -o minimemory/minimemory.o
miniVector/miniVector.o:miniVector/miniVector.cpp
	g++ -c miniVector/miniVector.cpp -o miniVector/miniVector.o
clean:
	rm miniVector.out minimemory/minimemory.o miniVector/miniVector.o