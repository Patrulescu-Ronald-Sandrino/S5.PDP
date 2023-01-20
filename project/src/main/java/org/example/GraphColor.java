package org.example;

import java.awt.Color;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

// TODO: remove class if not used
public class GraphColor {
    public static final int MAX_NUMBER_OF_COLORS = ((int) Math.pow(256, 3));

    public static List<Color> generateSetAmountOfColors(int setAmount){
        List<Color> colors = new ArrayList<>();

        if (setAmount > MAX_NUMBER_OF_COLORS){
            throw new RuntimeException("Chief, you can't generate more than 256^3 colors. Greedy bastard.");
        }

        boolean[][][] isColorGenerated = new boolean[256][256][256];

        int colorIndex = 0;
        while(colorIndex < setAmount){
            int r = new Random().nextInt(0, 256);
            int g = new Random().nextInt(0, 256);
            int b = new Random().nextInt(0, 256);

            if(!isColorGenerated[r][g][b]) {
                isColorGenerated[r][g][b] = true;
                colors.add(new Color(r, g, b));
                colorIndex++;
            }
        }

        return colors;
    }
}
