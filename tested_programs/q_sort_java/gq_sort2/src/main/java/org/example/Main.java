package org.example;

import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
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
                data[i] = random.nextInt(500) * 2;  // Generate even numbers up to 1000
            }
        }

        System.out.println("Unsorted Array");
        System.out.println(Arrays.toString(data));

        int size = data.length;

        Quicksort.quickSort(data, 0, size - 1);

        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(data));
    }

    static class Quicksort {

        static int partition(int[] array, int low, int high) {
            int pivot = array[high];
            int i = low;

            for (int j = low; j < high; j++) {
                if (array[j] < pivot) {
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                    i++;
                }
            }

            int temp = array[i];
            array[i] = array[high];
            array[high] = temp;

            return i;
        }

        static void quickSort(int[] array, int low, int high) {
            if (low < high) {
                int pi = partition(array, low, high);
                quickSort(array, low, pi - 1);
                quickSort(array, pi + 1, high);
            }
        }
    }
}