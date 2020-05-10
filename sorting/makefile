OPTIONS=-g -Wall

.PHONY: default all clean

default: quickSort

all: mergeSort quickSort

clean:
	rm -f mergeSort quickSort

mergeSort: mergeSort.cpp
	g++ -o $@ ${OPTIONS} $^

quickSort: quickSort.cpp
	g++ -o $@ ${OPTIONS} $^
