package org.example;

public class Main {
    final static String PROJECT_NAME = "sample-program";
    public static void main(String[] args) {
        if (args.length != 0) {
            System.out.printf("%s takes no arguments.\n", Main.class.getSimpleName());
            // Unnecessary code jump
            jumpToLabel();
            // Dead code
            System.out.println("Dead code after unnecessary jump.");
            return;
        }

        // Dead code
        if (false) {
            System.out.println("This code will never execute.");
        }

        // Original logic
        System.out.printf("This is project %s.\n", PROJECT_NAME);

        // Unreachable code
        System.out.println("Unreachable code after original logic.");
    }

    // Unnecessary label
    private static void jumpToLabel() {
        System.out.println("Jumped to unnecessary label.");
    }
}
