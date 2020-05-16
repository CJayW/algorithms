//INFO: https://en.wikipedia.org/wiki/Selection_sort
//O(n^2). No added memory

#include <iostream>
#include <limits>
#include <string.h>

#include <math.h>

void printItems(int const items[],
                const int total,
                int inc = 1)
{

  if(inc < 1)
    inc = 1;

  for(int i = 0; i < total; i += inc) {
    std::cout << items[i] << " ";
  }

  std::cout << std::endl;
}

void selectionSort(int* buf, int len) {

    #define SWAP(_pos1, _pos2) \
      do{ \
        int tmp = buf[_pos1]; \
        buf[_pos1] = buf[_pos2]; \
        buf[_pos2] = tmp; \
      }while(0); 

    //I is the divider between the sorted and unsorted array
    for(int i = 0; i < len - 1; i++) {
      int minIndex = i;
      int min = buf[minIndex];

      for(int j = i+1; j < len; j++) {
        if(buf[j] < min) {
          min = buf[j];
          minIndex = j;
        }
      }

      SWAP(i, minIndex);
    }

    #undef SWAP
}

int main() {

  srand(time(nullptr));

  int total = 100000;

  int* arr = new int[total]();
  for(int i = 0; i < total; i++) {
    arr[i] = rand();
  }

  std::cout << "Starting sort" << std::endl;

  selectionSort(arr, total);

  printItems(arr, total, 100);

  //Checks for errors
  for(int i = 1; i < total; i++) {
    if(arr[i] < arr[i-1])
      std::cerr << "Sorting Error" << std::endl;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
