package org.example;

import java.util.Arrays;
import java.util.Random;
import java.util.function.Function;
import java.util.stream.IntStream;

public class Main {
    public static void main(String args[]) {
        int size;
        int[] data = new int[0];
        Random random = new Random();
        Function<String, Integer> converter = str -> Integer.parseInt(str);
        Function<Integer, Integer> randomGenerator = i -> random.nextInt(1000);

        while(true) {
            if (args.length > 0) {
                data = IntStream.range(0, args.length).map(i -> converter.apply(args[i])).toArray();
                break;
            } else {
                size = 100;
                data = IntStream.range(0, size).map(i -> randomGenerator.apply(i)).toArray();
                break;
            }
        }

        System.out.println("Unsorted Array");
        System.out.println(Arrays.toString(data));

        Quicksort.quickSort(data, 0, data.length - 1);

        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(data));
    }

    static class Quicksort {
        static int partition(int array[], int low, int high) {
            int pivot = array[high];
            int i = (low - 1);
            int j;
            for (j = low; j < high; j++) {
                if (array[j] <= pivot) {
                    i++;
                    swap(array, i, j);
                }
            }
            swap(array, i + 1, high);
            return (i + 1);
        }

        static void quickSort(int array[], int low, int high) {
            if (low < high) {
                int pi = partition(array, low, high);
                quickSort(array, low, pi - 1);
                quickSort(array, pi + 1, high);
            }
        }

        static void swap(int[] array, int i, int j) {
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
}