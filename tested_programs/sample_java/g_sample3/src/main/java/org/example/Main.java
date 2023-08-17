package org.example;

public class Main {
    final static String PROJECT_NAME = "sample-program";
    public static void main(String[] args) {
        try {
            if (args.length != 0) {
                System.out.printf("%s takes no arguments.\n", Main.class.getSimpleName());
                throw new Exception();
            }
        } catch (Exception e) {
            return;
        } finally {
            System.out.printf("This is project %s.\n", PROJECT_NAME);
            try {
                if(args.length == 0) {
                    throw new Exception();
                }
            } catch (Exception e) {
                return;
            }
        }

        int a = 0;
        while (a < 0) { // Dead code
            System.out.println("This is dead code");
            a++;
        }

        for (int i = 0; i < 0; i++) { // Unnecessary code
            System.out.println("This is unnecessary code");
        }

        do { // Code jumps
            System.out.println("This is a code jump");
        } while (false);
    }
}