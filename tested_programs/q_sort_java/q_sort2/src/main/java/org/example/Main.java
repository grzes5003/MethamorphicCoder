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

        Arrays.sort(data); // Using built-in sorting method

        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(data));
    }
}
