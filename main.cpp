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

const int SIZE = 10; //size of the array being sorted. Change this to change the size.

int main(int argc, const char * argv[]) {
    int sortableArray[SIZE]; //array to be sorted
    srand(time(0)); //seed rand for filling the array
    arrayFiller(sortableArray); //fill the array
    
    for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }
    
    int startSortIndex = -1;
    do {
        swapSort(sortableArray, ++startSortIndex);
        //cout << count++ << endl;
    } while (!bubbleSort(sortableArray, startSortIndex));
    for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }
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
 
 Current problem:
 Every time we take a pass with bubblesort, the first and last elements are guaranteed to be in place
 We need to leave the first and last elements out of the split calculations. 
 So how do we do this mathmatically?
 Maybe we could precompute the split locations with each pass, but that includes the creation of an array which is obnoxious. Maybe though. 
 
*/

inline void swapSort(int sortableArray[], int skipNum){
            /*int endIndex = (skipNum+(SIZE/2))-1;
            
            for (int j = 0; j <= endIndex-skipNum; ++j) {
                int currentIndex = j+skipNum;
                
                int indexToCheck = (-1-j)+(SIZE);
                
                if (sortableArray[currentIndex] > sortableArray[indexToCheck]) swap(currentIndex, indexToCheck, sortableArray);
            }*/
    for (int split = 1; split <= SIZE; split*=2) {
        for (int i = 0; i < split; ++i) {
            int startIndex = (i*(SIZE/split))+skipNum;
            int endIndex = (((SIZE-1)-startIndex)/(split*2))*(i+1);
            //this doesn't work. Commented out for posterity
            //int endIndex = startIndex+((SIZE/(split*2))-1-skipNum);
            
            for (int j = 0; j <= endIndex-startIndex; ++j) {
                int currentIndex = j+startIndex;
                
                int indexToCheck = (startIndex-j-1)+(SIZE/split)-skipNum;
                
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

