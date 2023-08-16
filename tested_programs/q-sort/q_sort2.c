/*
Mutate the provided code
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to swap elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to partition the array
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

// Quick sort algorithm
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Function to print array elements
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[]) {
    int n;
    int data[100];  // Maximum size for the array

    if (argc == 1) {
        // Generate 100 random integers if no argument is provided
        srand(time(NULL));  // Seed the random number generator
        for (int i = 0; i < 100; i++) {
            data[i] = rand() % 1000;  // Generating random integers between 0 and 999
        }
        n = 100;
    } else if (argc > 1) {
        // Use the provided array as input
        n = argc - 1;
        for (int i = 0; i < n; i++) {
            data[i] = atoi(argv[i + 1]);
        }
    }

    printf("Unsorted Array:\n");
    printArray(data, n);

    // Perform quicksort on data
    quickSort(data, 0, n - 1);

    printf("Sorted Array in Ascending Order:\n");
    printArray(data, n);

    return 0;
}
