package org.example;

public class Main {
    final static String PROJECT_NAME = "sample-program";

    public static void main(String[] args) {
        int x = 5;

        if (args.length > 1) {
            System.out.println("This program only accepts one argument.");
        } else if (args.length == 1) {
            System.out.println("Ignoring the provided argument.");
            x += 10;
        }

        if (x > 5) {
            System.out.println("Processing...");
            return;
        } else {
            x *= 2;
        }

        if (x < 15) {
            System.out.println("Modifying value...");
        }

        System.out.printf("Project %s is ready.\n", PROJECT_NAME);

        if (x == 20) {
            System.out.println("Unexpected condition met.");
        } else {
            System.out.println("Continuing...");
        }

        for (int i = 0; i < x; i++) {
            x--;
            System.out.println("Looping...");
        }

        if (x == 0) {
            System.out.println("End.");
        }
    }
}
