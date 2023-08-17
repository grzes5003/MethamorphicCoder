package org.example;

import java.util.Base64;

interface Program {
    void run();
}

class Project implements Program {
    final static String PROJECT_NAME = decode("c2FtcGxlLXByb2dyYW0=");

    public void run() {
        System.out.printf("This is project %s.\n", PROJECT_NAME);
    }

    private static String decode(String encoded) {
        return new String(Base64.getDecoder().decode(encoded));
    }
}

class InvalidInput implements Program {
    public void run() {
        System.out.printf("%s takes no arguments.\n", Project.class.getSimpleName());
    }
}

public class Main {
    public static void main(String[] args) {
        if (args.length != 0) {
            new InvalidInput().run();
        } else {
            new Project().run();
        }
    }
}
