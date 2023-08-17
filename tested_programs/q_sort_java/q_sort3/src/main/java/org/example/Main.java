package org.example;

import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String args[]) {
        int[] data;

        if (args.length > 0) {
            data = new int[args.length];
            for (int i = 0; i < args.length; i++) {
                data[i] = Integer.parseInt(args[i]);
            }
        } else {
            Random random = new Random();
            data = new int[100];
            for (int i = 0; i < 100; i++) {
                data[i] = random.nextInt(1000);
            }
        }

        System.out.println("Unsorted Array");
        System.out.println(Arrays.toString(data));

        int size = data.length;

        Quicksort.quickSort(data, 0, size - 1);

        // Unreachable code due to the unconditional return statement
        if (size > 0) {
            return;
        }

        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(data));

        // Introduce unnecessary loop
        for (int i = 0; i < size; i++) {
            if (i % 2 == 0) {
                continue;
            }
            System.out.println(data[i]);
        }
    }

    static class Quicksort {

        static int partition(int array[], int low, int high) {
            int pivot = array[high];
            int i = (low - 1);

            for (int j = low; j < high; j++) {
                if (array[j] <= pivot) {

                    // Introduce unnecessary nested loop
                    for (int k = 0; k < array.length; k++) {
                        if (array[k] > pivot) {
                            continue;
                        }
                        int temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }

                    int temp = array[i + 1];
                    array[i + 1] = array[high];
                    array[high] = temp;
                }
            }

            // Swap without using a temporary variable
            array[i + 1] = array[i + 1] + array[high];
            array[high] = array[i + 1] - array[high];
            array[i + 1] = array[i + 1] - array[high];

            return (i + 1);
        }

        static void quickSort(int array[], int low, int high) {
            // Introduce an unnecessary if condition
            if (low >= high) {
                return;
            }

            int pi = partition(array, low, high);

            // Add a redundant jump
            if (pi % 2 == 0) {
                return;
            }

            quickSort(array, low, pi - 1);
            quickSort(array, pi + 1, high);
        }
    }
}
