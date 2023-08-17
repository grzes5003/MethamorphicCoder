package org.example;

public class Main {
    final static String PROJECT_NAME = "sample-program";
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.printf("%s takes no arguments.\n", args[0]);
            return;
        }
        System.out.printf("This is project %s.\n", PROJECT_NAME);
    }
}