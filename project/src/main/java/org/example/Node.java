package org.example;

import java.util.Objects;

public class Node {
    private int value;
    private int weight;
    private int colorIndex;

    public Node(int nodeValue, int nodeWeight) {
        this.value = nodeValue;
        this.weight = nodeWeight;
        this.colorIndex = -1;
    }

    public int getWeight() {
        return weight;
    }

    public void setWeight(int weight) {
        this.weight = weight;
    }

    public int getValue() {
        return value;
    }

    public void setValue(int value) {
        this.value = value;
    }

    public int getColorIndex() {
        return colorIndex;
    }

    public void setColorIndex(int colorIndex) {
        this.colorIndex = colorIndex;
    }

    public boolean isColored() {
        return this.colorIndex >= 0;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Node node = (Node) o;
        return this.getValue() == node.getValue();
    }

    @Override
    public int hashCode() {
        return Objects.hash(value);
    }

    @Override
    public String toString() {
        return "Node{" +
                "value=" + value +
                ", weight=" + weight +
                ", colorIndex=" + colorIndex +
                '}';
    }
}
