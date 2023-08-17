package org.example;

import java.util.Random;

public class Main {
    final static String PROJECT_NAME = "sample-program";

    public static void main(String[] args) {
        Random rand = new Random();
        int randomInt = rand.nextInt(50);

        // Unnecessary code jumps and dead code
        switch(randomInt) {
            case 1:
                System.out.println("This would print if randomInt equals 1");
                break;
            default:
                checkArgs(args);
                break;
        }
    }

    private static void checkArgs(String[] args) {
        boolean checkArgs = args.length != 0;
        boolean deadCode = false;
        if (deadCode) {
            System.out.println("This is dead code. It will never be executed.");
        } else {
            if (checkArgs) {
                System.out.printf("%s takes no arguments.\n", Main.class.getSimpleName());
                System.exit(0);
            } else {
                printProjectName();
            }
        }
    }

    private static void printProjectName() {
        String projectName = PROJECT_NAME;
        // Unnecessary loop
        for (int i = 0; i < 1; i++) {
            System.out.printf("This is project %s.\n", projectName);
        }
    }
}