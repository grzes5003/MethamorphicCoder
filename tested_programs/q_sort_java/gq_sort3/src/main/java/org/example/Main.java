package org.example;

import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String args[]) {
        int[] data;
        int size = 0;

        if (args.length > 0) {
            data = new int[args.length];
            for (int i = 0; i < args.length; i++) {
                data[i] = Integer.parseInt(args[i]);
            }
            gotoPrintUnsortedData:
            System.out.println("Unsorted Array");
            System.out.println(Arrays.toString(data));
        }
        else {
            Random random = new Random();
            data = new int[100];
            for (int i = 0; i < 100; i++) {
                data[i] = random.nextInt(1000);
            }
            size = data.length;
            if(size == 100) {
                gotoPrintUnsortedData:
                System.out.println("Unsorted Array");
                System.out.println(Arrays.toString(data));
            }
        }

        int temp = 0; // Dead code
        int size_temp = size; // Dead code, unnecessary

        Quicksort.quickSort(data, 0, size - 1);

        if(size_temp == size) { // Unnecessary code
            System.out.println("Sorted Array in Ascending Order: ");
            System.out.println(Arrays.toString(data));
        }
    }

    static class Quicksort {

        static int partition(int array[], int low, int high) {
            int pivot = array[high];
            int i = (low - 1);

            for (int j = low; j < high; j++) {
                if (array[j] <= pivot) {
                    i++;
                    int temp = array[i];
                    array[i] = array[j];
                    array[j] = temp;
                }
                else {
                    continue; // Unnecessary jump
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
                quickSort(array, low, pi - 1);
                quickSort(array, pi + 1, high);
            }
            else {
                return; // Unnecessary jump
            }
        }
    }
}