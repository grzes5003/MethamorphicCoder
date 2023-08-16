/*
Modify the code below using all known obfuscation techniques but keep the original logic intact. Use polymorphism and metamorphism techniques.
Make as much changes as possible. Make sure compiled machine code from edited code will be much different from the original, making it hard to identify.
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int DataType;

typedef struct {
    DataType value;
} Element;

void swap(Element *a, Element *b) {
    Element t = *a;
    *a = *b;
    *b = t;
}

int partition(Element array[], int low, int high) {
    Element pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j].value <= pivot.value) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(Element array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

void printArray(Element array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i].value);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    Element data[100];

    srand(time(NULL));

    if (argc == 1) {
        for (int i = 0; i < 100; i++) {
            data[i].value = rand() % 1000;
        }
    } else if (argc > 1) {
        int n = argc - 1;
        for (int i = 0; i < n; i++) {
            data[i].value = atoi(argv[i + 1]);
        }
    }

    printf("Unsorted Array\n");
    printArray(data, 100);

    quickSort(data, 0, 99);

    printf("Sorted array in ascending order:\n");
    printArray(data, 100);

    return 0;
}
