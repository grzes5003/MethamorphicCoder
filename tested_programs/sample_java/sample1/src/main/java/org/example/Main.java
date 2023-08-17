package org.example;

public class Main {
    final static String PROJECT_NAME = "sample-program";
    public static void main(String[] args) {
        if (args.length != 0) {
            System.out.printf("%s takes no arguments.\n", Main.class.getSimpleName());
            return;
        }
        System.out.printf("This is project %s.\n", PROJECT_NAME);
    }
}