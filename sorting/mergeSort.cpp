//Info https://en.wikipedia.org/wiki/Merge_sort

//Implementation Review:
//mergeSortStack - Stores the output arrays on the stack
//    Handles upto 600,000 elements before stack overflow
//mergeSortNew   - Stores the output arrays on the heap using new
//    Handles upto 2,000,000 elements before stack overflow


#include <iostream>
#include <limits>
#include <alloca.h>

void printItems(int items[], int total) {
  for(int i = 0; i < total; i++) {
    std::cout << items[i] << " ";
  }

  std::cout << std::endl;
}

//Sorts the passed items array
//Stack overflows at 600,000 items
void mergeSortStack(int items[], int total, int outputArr[]) {

  if(!outputArr) {
    outputArr = items;
  }

  if(total == 1) {
    outputArr[0] = items[0];
    return;
  }

  int dividerIndex = total / 2;

  int len1 = dividerIndex;
  int arr1[len1];

  int len2 = total - dividerIndex;
  int arr2[len2];

  mergeSortStack(items, len1, arr1);
  mergeSortStack(items + dividerIndex, len2, arr2);

  int index1 = 0, index2 = 0, writeIndex = 0;

  //Sorts the elements until one array is finished
  while(index1 < len1 && index2 < len2) {
    if(arr1[index1] < arr2[index2]) {
      outputArr[writeIndex++] = arr1[index1++];
    }else{
      outputArr[writeIndex++] = arr2[index2++];
    }
  }

  //Adds any remaining elements
  //One array will be completed, the other will not be

  while(index1 < len1)
    outputArr[writeIndex++] = arr1[index1++];

  while(index2 < len2)
    outputArr[writeIndex++] = arr2[index2++];

}

//Stack overflows at 2,000,000 items
void mergeSortNew(int items[], int total, int outputArr[]) {

  if(!outputArr) {
    outputArr = items;
  }

  if(total == 1) {
    outputArr[0] = items[0];
    return;
  }

  int dividerIndex = total / 2;

  int len1 = dividerIndex;
  int* arr1 = new int[len1]();

  int len2 = total - dividerIndex;
  int* arr2 = new int[len2]();

  if(!arr1 || !arr2) {
    std::cerr << "New failed" << std::endl;
    exit(1);
  }

  mergeSortNew(items, len1, arr1);
  mergeSortNew(items + dividerIndex, len2, arr2);

  int index1 = 0, index2 = 0, writeIndex = 0;

  //Sorts the elements until one array is finished
  while(index1 < len1 && index2 < len2) {
    if(arr1[index1] < arr2[index2]) {
      outputArr[writeIndex++] = arr1[index1++];
    }else{
      outputArr[writeIndex++] = arr2[index2++];
    }
  }

  //Adds any remaining elements
  //One array will be completed, the other will not be

  while(index1 < len1)
    outputArr[writeIndex++] = arr1[index1++];

  while(index2 < len2)
    outputArr[writeIndex++] = arr2[index2++];

}


int main() {

  int total = 3000000;
  int arr[total];

  for(int i = 0; i < total; i++) {
    arr[i] = rand();    
  }

  mergeSortNew(arr, sizeof(arr) / sizeof(int), NULL);
  printItems(arr, sizeof(arr) / sizeof(int));

  for(int i = 1; i < total; i++) {
    if(arr[i] < arr[i-1])
      std::cerr << "Sorting Error" << std::endl;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
