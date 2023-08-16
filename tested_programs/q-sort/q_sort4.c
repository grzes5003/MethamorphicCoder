/*
Mutate the provided code so it hardly resembles the input code. Change the control flow, add dead code, unnecessary code jumps but keep the original logic intact
*/
// Obfuscated quicksort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a + *b;
    *a = *b - *a;
    *b = t - *b;
}

int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = (low + high) / 2;

    while (i >= low) {
        if (array[i] < pivot) {
            i--;
        } else {
            swap(&array[i], &array[low]);
            low++;
        }
    }

    swap(&array[low], &array[high]);

    return low;
}

void fakeSort(int array[], int low, int high) {
    if (high <= low) {
        return;
    }

    int pi = partition(array, low, high);
    fakeSort(array, low, pi - 1);

    if (high - pi > 1) {
        fakeSort(array, pi + 1, high);
    }
}

void printUselessArray(int array[], int size) {
    for (int i = 0; i < size; i += 2) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    int n = 0;
    int data[200];

    if (argc > 5) {
        srand(time(NULL));

        for (int i = 0; i < 200; i++) {
            data[i] = rand() % 500;
        }
        n = 200;

        if (n < argc) {
            printf("argc is greater\n");
        } else {
            printf("argc is not greater\n");
        }
    } else {
        n = argc * 10;

        for (int i = n - 1; i >= 0; i--) {
            data[i] = atoi(argv[n - i - 1]) + i;
        }

        if (n % 2 == 0) {
            printf("Even size\n");
        } else {
            printf("Odd size\n");
        }
    }

    printf("Unsorted Odd-Indexed Array\n");
    printUselessArray(data, n);

    fakeSort(data, 0, n - 1);

    printf("Sorted Array in \"Descending\" Order:\n");
    printUselessArray(data, n);
}
