package org.example;

import java.awt.*;
import java.util.*;
import java.util.List;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.Collectors;


public class Graph {
    private final List<Color> colors;
    private final Map<Node, Set<Node>> neighbors;

    private final Set<Node> achromaticNodes;
    private final ExecutorService executorService;

    public Graph(int verticesCount) {
        executorService = Executors.newFixedThreadPool(8);

        this.colors = GraphColor.generateSetAmountOfColors(verticesCount);

        neighbors = new HashMap<>();
        this.generateVertices(verticesCount);

        achromaticNodes = new LinkedHashSet<>(neighbors.keySet());
    }

    private void generateVertices(int verticesCount) {
        for (int verticeIndex = 0; verticeIndex < verticesCount; verticeIndex++) {
            Node node = new Node(verticeIndex, new Random().nextInt(0, 100));
            neighbors.put(node, new LinkedHashSet<>());
        }
    }

    private int getVerticesCount() {
        return neighbors.keySet().size();
    }

    public void addEdge(int firstNodeValue, int secondNodeValue) {
        Node firstNode = neighbors.keySet().stream().filter(node -> node.getValue() == firstNodeValue).toList().get(0);
        Node secondNode = neighbors.keySet().stream().filter(node -> node.getValue() == secondNodeValue).toList().get(0);
        neighbors.get(firstNode).add(secondNode);
        neighbors.get(secondNode).add(firstNode);
    }

    public List<Node> getNeighbors(Node node) {
        return getNeighbors(node, NeighborType.ALL);
    }

    public List<Node> getNeighbors(Node node, NeighborType neighborType) {
        return switch (neighborType) {
            case COLORED -> neighbors.get(node).stream().filter(Node::isColored).toList();
            case UNCOLORED -> neighbors.get(node).stream().filter(node1 -> !node1.isColored()).toList();
            default -> neighbors.get(node).stream().toList();
        };
    }

    public List<Map.Entry<Integer, Integer>> getColors() {
        List<Map.Entry<Integer, Integer>> colors = new ArrayList<>();
        for (Node node : neighbors.keySet()) {
            colors.add(new AbstractMap.SimpleImmutableEntry<>(node.getValue(), node.getColorIndex()));
        }
        return colors;
    }

    public List<Integer> getWeights() {
        List<Integer> weights = new ArrayList<>(getVerticesCount());
        for (Node node : neighbors.keySet())
            weights.set(node.getValue(), node.getWeight());
        return weights;
    }

    public int getMaxColorIndex() {
        int maxColorIndex = 0;
        for (Node node : neighbors.keySet())
            if (neighbors.get(node).size() > maxColorIndex)
                maxColorIndex = neighbors.get(node).size();
        return maxColorIndex + 1;
    }

    public void computeAndSetNodeColor(Node node) {
        Set<Node> neighborNodes = neighbors.get(node);
        Set<Integer> neighborColors = neighborNodes.stream().map(Node::getColorIndex).collect(Collectors.toSet());
        int maximumNeighborColor = Collections.max(neighborColors);

        for (int i = 0; i <= maximumNeighborColor + 1; i++)
            if (!neighborColors.contains(i))
                node.setColorIndex(i);
    }

    /// returns the heaviest node, or, in case of an equality, the node with the lowest value
    private boolean isNodeHeaviest(Node node) {
        for (Node neighborNode : getNeighbors(node, NeighborType.UNCOLORED)) {
            if (neighborNode.getWeight() > node.getWeight())
                return false;
            else if (neighborNode.getWeight() == node.getWeight() && node.getValue() > neighborNode.getValue())
                return false;
        }
        return true;
    }

    public Set<Node> computeHeavyNodes() {
        List<Future<Boolean>> futureList = new ArrayList<>();
        List<Node> nodeList = new ArrayList<>(achromaticNodes);
        Set<Node> result = new LinkedHashSet<>();
        for (Node node : achromaticNodes) {
            Future<Boolean> f = executorService.submit(() -> isNodeHeaviest(node));
            futureList.add(f);
        }
        for (int i = 0; i < achromaticNodes.size(); i++) {
            try {
                if (futureList.get(i).get())
                    result.add(nodeList.get(i));
            } catch (InterruptedException | ExecutionException e) {
                e.printStackTrace();
            }
        }
        return result;
    }

    public void colorGraph() {
        while (!achromaticNodes.isEmpty()) {
            Set<Node> heavyNodes = computeHeavyNodes();
            for (Node node : heavyNodes) {
                executorService.submit(() -> {
                    computeAndSetNodeColor(node);
                });
            }
            achromaticNodes.removeAll(heavyNodes);
        }
        executorService.shutdown();
    }

    public void showGraph() {
        System.out.println("Colors: ");
        neighbors.keySet().forEach(node -> {
            System.out.println(node.getValue() + " has color " + node.getColorIndex());
        });

        System.out.println(" ");

        System.out.println("Neighbours: ");
        neighbors.forEach((node, nodes) -> {
            System.out.println(node.getValue() + " -> " + nodes.stream()
                    .map(Node::getValue)
                    .map(Objects::toString)
                    .reduce("", (a, b) -> a + " " + b));
        });

        System.out.println(" ");

        System.out.println("Neighbours (as colors): ");
        neighbors.forEach((node, nodes) -> {
            System.out.println(node.getColorIndex() + " -> " + nodes.stream()
                    .map(Node::getColorIndex)
                    .map(Objects::toString)
                    .reduce("", (a, b) -> a + " " + b));
        });
    }

    public int[][] toMatrix() {
        int[][] matrix = new int[getVerticesCount()][getVerticesCount()];
        for (int row = 0; row < getVerticesCount(); row++) {
            for (int column = 0; column < getVerticesCount(); column++) {
                matrix[row][column] = 0;
            }
        }
        for (Node node : neighbors.keySet()) {
            for (Node neighbour : neighbors.get(node)) {
                matrix[node.getValue()][neighbour.getValue()] = 1;
            }
        }
        return matrix;
    }
}
