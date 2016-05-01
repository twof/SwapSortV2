//
//  main.cpp
//  SwapSortV2
//
//  Created by fnord on 1/5/16.
//  Copyright © 2016 fnord. All rights reserved.
//

#include <iostream>
#include <thread>
#include <time.h>

using namespace std;

inline void arrayFiller(int sortableArray[]);
inline void swapSort(int sortableArray[], int skipNum);
inline void swap(int indexA, int indexB, int sortableArray[]);
inline bool bubbleSort(int sortableArray[], int startIndex);

const int SIZE = 1000000; //size of the array being sorted. Change this to change the size.

int main(int argc, const char * argv[]) {
    int sortableArray[SIZE]; //array to be sorted
    srand(time(0)); //seed rand for filling the array
    arrayFiller(sortableArray); //fill the array
    
    /*for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }*/
    
    int startSortIndex = -1;
    do {
        swapSort(sortableArray, ++startSortIndex);
        //cout << count++ << endl;
    } while (!bubbleSort(sortableArray, startSortIndex));
    /*for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }*/
    return 0; //end
}

inline void arrayFiller(int sortableArray[]){
    for (int i=0; i<SIZE; ++i){
        sortableArray[i] = rand()%SIZE; //fill the array with numbers between 1 and 10000000
    }
}
/*
 How this currently works:
 1. Start by splitting the array once. Elements will be swapped from the outside in on oposite sides of each pair of consecutive split
 2. Check everything from the outside in. Swap when necisary.
 3. Continue splitting and swapping until the number of splits is greater than the size of the array
 
 Last Solution:
 Used adjusted size rather than actual size. This prevents overlapping.
 
 Current Problem:
 
 
*/

inline void swapSort(int sortableArray[], int skipNum){
    const int ADJUSTED_SIZE = SIZE - (skipNum*2);
    
    for (int split = 1; split <= ADJUSTED_SIZE/16; split*=2) { //16 is a magic number right now. Need to figure out how to optimally compute the number that should go there
        for (int i = 0; i < split; ++i) {
            int startIndex = skipNum+(i*(ADJUSTED_SIZE/split));
            int endIndex = (startIndex+(ADJUSTED_SIZE/(split*2)))-1;
            
            for (int j = 0; j <= endIndex-startIndex; ++j) {
                int currentIndex = j+startIndex;
                
                int indexToCheck = (startIndex-j-1)+(ADJUSTED_SIZE/split);
                
                if (sortableArray[currentIndex] > sortableArray[indexToCheck]) swap(currentIndex, indexToCheck, sortableArray);
            }
        }
    }
}

inline void swap(int indexA, int indexB, int sortableArray[]){
    int temp = sortableArray[indexA];
    sortableArray[indexA] = sortableArray[indexB];
    sortableArray[indexB] = temp;
}

inline bool bubbleSort(int sortableArray[], int startIndex){
    bool sorted = true;
    
    for (int i=startIndex; i<SIZE-startIndex-1; ++i){
        if (sortableArray[i]>sortableArray[i+1]) {
            swap(i, i+1, sortableArray);
            sorted = false;
        }
    }
    
    if (!sorted){
        for (int i = SIZE-startIndex-1; i > startIndex; --i) {
            if (sortableArray[i]<sortableArray[i-1]) {
                swap(i, i-1, sortableArray);
                sorted = false;
            }
        }
    }
    
    return sorted;
}

