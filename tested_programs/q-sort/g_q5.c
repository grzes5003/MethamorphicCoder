#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE 100
#define MAX_RAND_VALUE 1000

typedef struct _sorter {
    void (*sort)(struct _sorter*, int*, int, int);
} sorter;

typedef struct _printer {
    void (*print)(struct _printer*, int*, int);
} printer;

void exchange(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int divide(int* array, int low, int high) {
    int pivot = array[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            exchange(&array[i], &array[j]);
        }
    }

    exchange(&array[i + 1], &array[high]);
    return (i + 1);
}

void sort(sorter* s, int* array, int low, int high) {
    if (low < high) {
        int pi = divide(array, low, high);
        s->sort(s, array, low, pi - 1);
        s->sort(s, array, pi + 1, high);
    }
}

void print(printer* p, int* array, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d  ", array[i]);
    }
    printf("\n");
}

sorter s = {.sort = sort};
printer p = {.print = print};

void populateWithRandom(int* array, int size) {
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % MAX_RAND_VALUE;
    }
}

void populateWithArgs(int* array, char* args[], int size) {
    for (int i = 0; i < size; i++) {
        array[i] = atoi(args[i + 1]);
    }
}

int main(int argc, char* argv[]) {
    int n;
    int data[MAX_ARRAY_SIZE];

    if (argc == 1) {
        populateWithRandom(data, MAX_ARRAY_SIZE);
        n = MAX_ARRAY_SIZE;
    } else if (argc > 1) {
        n = argc - 1;
        populateWithArgs(data, argv, n);
    }

    printf("Unsorted Array\n");
    p.print(&p, data, n);

    s.sort(&s, data, 0, n - 1);

    printf("Sorted array in ascending order:\n");
    p.print(&p, data, n);
}