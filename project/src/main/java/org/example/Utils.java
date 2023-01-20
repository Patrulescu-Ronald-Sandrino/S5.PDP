package org.example;

import java.util.List;
import java.util.Map;

public class Utils {
    public static int[] mapToIntArray(Map<Integer, Integer> map) {
        int[] array = new int[map.size()];
        int index = 0;
        for (Map.Entry<Integer, Integer> entry : map.entrySet()) {
            array[index] = entry.getValue();
            index++;
        }
        return array;
    }

    public static void printWithTID(Object object) {
        System.out.printf("[TID=%d] %s%n" ,Thread.currentThread().getId(), object);
    }
}
