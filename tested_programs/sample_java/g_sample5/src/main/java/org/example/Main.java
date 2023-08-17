package org.example;

public class Main {
    final static String a = new String(new char[] {115,97,109,112,108,101,45,112,114,111,103,114,97,109});

    public static void main(String[] b) {
        B b1 = new B();
        b1.c(b);
        b1.d();
    }
}

class B {
    void c(String[] b) {
        if (b.length != 0) {
            System.out.printf("%s" + " " + new String(new char[] {116,97,107,101,115,32,110,111,32,97,114,103,117,109,101,110,116,115,46,10}), Main.class.getSimpleName());
            System.exit(0);
        }
    }

    void d() {
        System.out.printf(new String(new char[] {84,104,105,115,32,105,115,32,112,114,111,106,101,99,116,32,37,115,46,10}), Main.a);
    }
}