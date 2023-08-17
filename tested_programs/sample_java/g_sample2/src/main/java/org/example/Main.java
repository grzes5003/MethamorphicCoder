package org.example;

public class Main {
    final static String PROJECT_NAME = "modified-program";

    public static void main(String[] args) {
        if (args.length > 0) {  // checking if there are any arguments
            System.out.printf("%s takes arguments.\n", Main.class.getSimpleName());
            for(String arg : args) { // printing out all arguments
                System.out.println(arg);
            }
        } else {
            System.out.printf("This is project %s.\n", PROJECT_NAME);
        }
    }
}