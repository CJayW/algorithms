OPTIONS=-g -Wall

.PHONY: default all clean

default: mergeSort

all: mergeSort

clean:
	rm -f mergeSort


mergeSort: mergeSort.cpp
	g++ -o $@ ${OPTIONS} $^
