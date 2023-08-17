package org.example;

import java.util.Arrays;
import java.util.Random;

public class Main {
    public static void main(String data[]) {
        int[] dataArray;

        if (data.length > 0) {
            dataArray = new int[data.length];
            for (int i = 0; i < data.length; i++) {
                dataArray[i] = Integer.parseInt(data[i]);
            }
        } else {
            Random random = new Random();
            dataArray = new int[100];
            for (int i = 0; i < 100; i++) {
                dataArray[i] = random.nextInt(1000);
            }
        }

        System.out.println("Unsorted Array");
        System.out.println(Arrays.toString(dataArray));

        int dataSize = dataArray.length;

        Quicksort.quickSort(dataArray, 0, dataSize - 1);

        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(dataArray));
    }

    static class Quicksort {

        static int divide(int arr[], int l, int h) {
            int pivot = arr[h];
            int i = (l - 1);

            for (int j = l; j < h; j++) {
                if (arr[j] <= pivot) {
                    i++;

                    int temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }

            int temp = arr[i + 1];
            arr[i + 1] = arr[h];
            arr[h] = temp;

            return (i + 1);
        }

        static void sort(int arr[], int l, int h) {
            if (l < h) {
                int p = divide(arr, l, h);
                sort(arr, l, p - 1);
                sort(arr, p + 1, h);
            }
        }

        static void quickSort(int arr[], int l, int h) {
            sort(arr, l, h);
        }
    }
}
