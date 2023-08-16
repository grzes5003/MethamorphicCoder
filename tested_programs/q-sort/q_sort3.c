/*
Mutate the provided code. Change the control flow, add dead code, unnecessary code jumps
but keep the original logic intact
*/

// Quick sort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// function to swap elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// function to find the partition position
int partition(int array[], int low, int high) {
    // select the rightmost element as pivot
    int pivot = array[high];
    // pointer for greater element
    int i = (low - 1);

    // traverse each element of the array
    // compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            // if element smaller than pivot is found
            // swap it with the greater element pointed by i
            i++;

            // swap element at i with element at j
            swap(&array[i], &array[j]);
        }
    }

    // swap the pivot element with the greater element at i
    swap(&array[i + 1], &array[high]);

    // return the partition point
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        // find the pivot element such that
        // elements smaller than pivot are on left of pivot
        // elements greater than pivot are on right of pivot
        int pi = partition(array, low, high);

        // introducing unnecessary code jumps
        if (pi % 2 == 0) {
            // Even partition index, jump to the left
            quickSort(array, low, pi - 1);
        } else {
            // Odd partition index, jump to the right
            quickSort(array, pi + 1, high);
        }
    }
}

// function to print array elements
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n;
    int data[100]; // Maximum size for the array

    if (argc == 1) {
        // Generate 100 random integers if no argument is provided
        srand(time(NULL)); // Seed the random number generator
        for (int i = 0; i < 100; i++) {
            data[i] = rand() % 1000; // Generating random integers between 0 and 999
        }
        n = 100;
    } else if (argc > 1) {
        // Use the provided array as input
        n = argc - 1;
        for (int i = 0; i < n; i++) {
            data[i] = atoi(argv[i + 1]);
        }
    }

    printf("Unsorted Array\n");
    printArray(data, n);

    // perform quicksort on data
    quickSort(data, 0, n - 1);

    // introducing dead code
    if (n % 2 == 0) {
        printf("Sorted array in ascending order (even length):\n");
    } else {
        printf("Sorted array in ascending order (odd length):\n");
    }

    printArray(data, n);
}
