OPTIONS=-g -Wall

.PHONY: default all clean

default: selectionSort

all: mergeSort quickSort selectionSort

clean:
	rm -f mergeSort quickSort selectionSort

mergeSort: mergeSort.cpp
	g++ -o $@ ${OPTIONS} $^

quickSort: quickSort.cpp
	g++ -o $@ ${OPTIONS} $^

selectionSort: selectionSort.cpp
	g++ -o $@ ${OPTIONS} $^

