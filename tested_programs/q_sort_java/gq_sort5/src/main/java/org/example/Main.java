package org.example;
import java.util.*;
interface Proc { void prc(int[] v, int a, int b); }
abstract class AbstProc implements Proc {
    protected Proc next;
    AbstProc(Proc next) { this.next = next; }
}
class PrtUnsorted extends AbstProc {
    PrtUnsorted(Proc next) { super(next); }
    public void prc(int[] v, int a, int b) {
        System.out.println("Unsorted Array");
        System.out.println(Arrays.toString(v));
        next.prc(v, a, b);
    }
}
class PrtSorted extends AbstProc {
    PrtSorted(Proc next) { super(next); }
    public void prc(int[] v, int a, int b) {
        QSort.qSort(v, a, b-1);
        System.out.println("Sorted Array in Ascending Order: ");
        System.out.println(Arrays.toString(v));
    }
}
class QSort {
    static void qSort(int[] arr, int f, int l) {
        if (f < l) {
            int pi = partition(arr, f, l);
            qSort(arr, f, pi - 1);
            qSort(arr, pi + 1, l);
        }
    }
    static int partition(int arr[], int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j=low; j<high; j++) {
            if (arr[j] <= pivot) {
                i++;
                int temp = arr[i]; arr[i] = arr[j]; arr[j] = temp;
            }
        }
        int temp = arr[i+1]; arr[i+1] = arr[high]; arr[high] = temp;
        return i+1;
    }
}
public class Main {
    public static void main(String args[]) {
        int[] arr;
        if (args.length > 0) {
            arr = new int[args.length];
            for (int i = 0; i < args.length; i++)
                arr[i] = Integer.parseInt(args[i]);
        } else {
            arr = new int[100];
            for (int i = 0; i < 100; i++)
                arr[i] = new Random().nextInt(1000);
        }
        Proc chain = new PrtUnsorted(new PrtSorted(null));
        chain.prc(arr, 0, arr.length);
    }
}