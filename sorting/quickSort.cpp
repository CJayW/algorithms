//Info https://en.wikipedia.org/wiki/Quicksort#Algorithm

#include <iostream>
#include <limits>

void printItems(int items[], int total) {
  for(int i = 0; i < total; i++) {
    std::cout << items[i] << " ";
  }

  std::cout << std::endl;
}


void quickSort(int* data, int len) {
  if(len < 2)
    return;

  int pivotIndex = len-1;
  int pivot = data[pivotIndex];


  for(int i = pivotIndex-1; i >= 0; i--) {


    if(data[i] > pivot) {
      int tmp2 = data[i];

      data[i] = data[pivotIndex-1];
      data[pivotIndex] = tmp2;
      pivotIndex--;

      //There is no need to update set the pivot value again
      // its already saved and will be set after the loop
    }
  }

  data[pivotIndex] = pivot;
  //Because the pivot starts at the end, there is no need to check for values less than the pivot

  quickSort(data, pivotIndex);
  quickSort(data + pivotIndex, len - pivotIndex);
}

int main() {

  int total = std::numeric_limits<int>().max() * 0.5;

  srand(time(nullptr));

  int* arr = new int[total]();
  for(int i = 0; i < total; i++) {
    arr[i] = rand();
  }

  std::cout << "Starting sort" << std::endl;

  quickSort(arr, total);

  {
    int inc = total / 100000;
    if(!inc) inc = 1;

    for(int i = 0; i < total; i += inc) {
      std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
  }

  //Checks for errors
  for(int i = 1; i < total; i++) {
    if(arr[i] < arr[i-1])
      std::cerr << "Sorting Error" << std::endl;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
