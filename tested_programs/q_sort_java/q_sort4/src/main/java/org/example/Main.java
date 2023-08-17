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
                if (i % 2 == 0) { // Introduce unnecessary if condition
                    data[i] = random.nextInt(1000);
                }
            }
        }

        System.out.println("Unsorted Array:");
        System.out.println(Arrays.toString(data));

        int size = data.length;

        Quicksort.quickSort(data, 0, size - 1);

        System.out.println("Sorted Array in Ascending Order:");
        System.out.println(Arrays.toString(data));
    }

    static class Quicksort {

        static int partition(int array[], int low, int high) {
            int pivot = array[high];
            int i = (low - 1);

            for (int j = low; j < high; j++) {
                if (array[j] <= pivot) {
                    i++;
                    if (j % 2 == 0) { // Introduce unnecessary if condition
                        int temp = array[i];
                        array[i] = array[j];
                        array[j] = temp;
                    }
                }
            }

            int temp = array[i + 1];
            array[i + 1] = array[high];
            array[high] = temp;

            return (i + 1);
        }

        static void quickSort(int array[], int low, int high) {
            if (low < high) {
                int pi = partition(array, low, high);
                if (low > high) { // Introduce unreachable if condition
                    quickSort(array, high, pi - 1);
                } else {
                    quickSort(array, low, pi + 1);
                }
            }
        }
    }
}
