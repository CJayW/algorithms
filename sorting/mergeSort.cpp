//Info https://en.wikipedia.org/wiki/Merge_sort

//Implementation Review:
//mergeSortNew   - Stores the output arrays on the heap using new
//    Handles upto 2,000,000 elements before stack overflow
//mergeSortNoRec - A non recursive implementation
//    Its more complex but has been tested using over 1 billion elements successfully
//    It doesn't do any dynamic allocation within its loop, its all preallocated

#include <iostream>
#include <limits>
#include <memory>
#include <alloca.h>
#include <string.h>

#include <math.h>

void printItems(int items[], int total) {
  for(int i = 0; i < total; i++) {
    std::cout << items[i] << " ";
  }

  std::cout << std::endl;
}

//resonably quick recursive mergeSort
//Suffers from a stack overflow when using a total over arrount 2 million ints
void mergeSortNew(int items[], int total, int outputArr[]) {

  if(!outputArr) {
    outputArr = items;
  }

  if(total == 1) {
    outputArr[0] = items[0];
    return;
  }

  int dividerIndex = total / 2;

  //This array could be placed on the stack, but it would stack overflow with less elements
  //One array could also be used as a output, which is then coppied onto the items array
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



//Uses buf as a tempororay memory storage buffer
void mergeSortNoRecStage(int* items, int len, int* buf) {
  if(len == 1)
    return;

  int div = len / 2;

  int len1 = div;
  int* arr1 = items;

  int len2 = len - div;
  int* arr2 = items + div;

  int writeIndex = 0, index1 = 0, index2 = 0;

  while(index1 < len1 && index2 < len2) {
    if(arr1[index1] < arr2[index2]) {
      buf[writeIndex++] = arr1[index1++];
    }else{
      buf[writeIndex++] = arr2[index2++];
    }
  }

  while(index1 < len1)
    buf[writeIndex++] = arr1[index1++];
  while(index2 < len2)
    buf[writeIndex++] = arr2[index2++];

  memcpy(items, buf, len * sizeof(int));
}

//Can handle arrays upto MAX_INT as long as their is enough memory
//Memory requirement:
// (ceil(log2(count)) + 1) * (1 + (4 * 2)) + count bytes
//Tested with arrays upto 1,073,741,823 elements
int mergeSortNoRec(int* items, int count) {

  //+1 because depth 0 is the whole array
  int maxDepth = ceil(log2(count)) + 1;

  int depth = -1;

  //Effectivly used as stacks with depth being the index of the head
  int* offsetHistory   = new int[maxDepth]();
  int* lengthHistory   = new int[maxDepth]();
  bool* isFirstHistory = new bool[maxDepth]();

  int* buf = new int[count]();

  {
    int len = count;
    while(true) {
      depth++;
      offsetHistory[depth] = 0;
      lengthHistory[depth] = len;
      isFirstHistory[depth] = true;

      if(len == 1)
        break;

      len /= 2;
    }
  }

  while(true) {
    //Sort the array assuming that the two higher halves are sorted
    mergeSortNoRecStage(items + offsetHistory[depth], lengthHistory[depth], buf);

    //Decrease the depth, and check if the whole array is sorted
    depth--;
    if(depth < 0)
      break;

    //Checks to see the array after the divider needs to be sorted
    if(!isFirstHistory[depth])
      continue;

    //Fills the stacks until the last length is 1
    isFirstHistory[depth] = false;

    int div = lengthHistory[depth] / 2;
    int offset = offsetHistory[depth] + div;

    int len = lengthHistory[depth] - div;
    while(true) {
      depth++;
      offsetHistory[depth] = offset;
      lengthHistory[depth] = len;
      isFirstHistory[depth] = true;

      if(len == 1)
        break;

      len /= 2;
    }
  }

  delete[] offsetHistory;
  delete[] lengthHistory;
  delete[] isFirstHistory;
  delete[] buf;
}

int main() {

  srand(time(nullptr));

  int total = std::numeric_limits<int>().max() * 0.5;

  int* arr = new int[total]();
  for(int i = 0; i < total; i++) {
    arr[i] = rand();
  }

  std::cout << "Starting sort" << std::endl;

  mergeSortNoRec(arr, total);
  printItems(arr, total);

  //Checks for errors
  for(int i = 1; i < total; i++) {
    if(arr[i] < arr[i-1])
      std::cerr << "Sorting Error" << std::endl;
  }

  std::cout << "Total: " << total << std::endl;

  return 0;
}
