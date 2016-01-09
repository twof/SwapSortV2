//
//  main.cpp
//  SwapSortV2
//
//  Created by fnord on 1/5/16.
//  Copyright © 2016 fnord. All rights reserved.
//

#include <iostream>
#include <time.h>

using namespace std;

inline void arrayFiller(int sortableArray[]);
inline void swapSort(int sortableArray[], int frontSkip, int backSkip);
inline void swap(int indexA, int indexB, int sortableArray[]);
inline bool bubbleSort(int sortableArray[], int finalIndex, int startIndex);

const int SIZE = 1000000; //size of the array being sorted. Change this to change the size.

int main(int argc, const char * argv[]) {
    int sortableArray[SIZE]; //array to be sorted
    srand(time(0)); //seed rand for filling the array
    arrayFiller(sortableArray); //fill the array
    
    /*for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }*/
    
    int finalSortIndex = SIZE;
    int startSortIndex = -1;
    do {
        --finalSortIndex;
        ++startSortIndex;
        swapSort(sortableArray, startSortIndex, finalSortIndex);
        //cout << count++ << endl;
    } while (!bubbleSort(sortableArray, finalSortIndex, startSortIndex));
    for (int i=0; i<SIZE;i++) {  //uncomment this for loop to print the sorted array. Commented out to test for time
        cout << i << ": " << sortableArray[i] << endl;
    }
    return 0; //end
}

inline void arrayFiller(int sortableArray[]){
    for (int i=0; i<SIZE; ++i){
        sortableArray[i] = rand()%1000000; //fill the array with numbers between 1 and 10000000
    }
}

inline void swapSort(int sortableArray[], int frontSkip, int backSkip){
    
    for (int split = 1; split <= SIZE/900000; split*=2) {
        
        for (int i = 0; i < split; ++i) {
            int startIndex = (i*(SIZE/split))+frontSkip;
            int endIndex = (startIndex+(SIZE/(split*2)))-1;
            
            for (int j = 0; j <= endIndex-startIndex; ++j) {
                int currentIndex = j+startIndex;
                
                int indexToCheck = (startIndex-j-1)+(SIZE/split);
                
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

inline bool bubbleSort(int sortableArray[], int finalIndex, int startIndex){
    bool sorted = true;
    
    for (int i=startIndex; i<finalIndex; ++i){
        if (sortableArray[i]>sortableArray[i+1]) {
            swap(i, i+1, sortableArray);
            sorted = false;
        }
    }
    if (!sorted){
        for (int i = finalIndex; i > startIndex; --i) {
            if (sortableArray[i]<sortableArray[i-1]) {
                swap(i, i-1, sortableArray);
                sorted = false;
            }
        }
    }
    //cout << counter << endl;
    
    return sorted;
}
