#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int* a, int* b) {
  int t = *a;
  *a = *b;
  *b = t;
}

int partition(int array[], int low, int high) {
  int pivot = array[high];
  int i = (low - 1);

  for (int j = low; j < high; j++) {
    if (array[j] <= pivot) {
      i++;
      swap(&array[i], &array[j]);
    }
  }

  swap(&array[i + 1], &array[high]);
  return (i + 1);
}

void quickSort(int array[], int low, int high) {
  if (low < high) {
    int pi = partition(array, low, high);
    quickSort(array, low, pi - 1);
    quickSort(array, pi + 1, high);
  }
}

void printArray(int array[], int size) {
  for (int i = 0; i < size; ++i) {
    printf("%d  ", array[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
    int n;
    int data[100];

    if (argc == 1) {
        srand(time(NULL));
        for (int i = 0; i < 100; i++) {
            data[i] = rand() % 1000;
        }
        n = 100;
    } else if (argc > 1) {
        n = argc - 1;
        for (int i = 0; i < n; i++) {
            data[i] = atoi(argv[i + 1]);
        }
    }

    printf("Unsorted Array\n");
    printArray(data, n);

    quickSort(data, 0, n - 1);

    printf("Sorted array in ascending order:\n");
    printArray(data, n);

    return 0;
}