package org.example;

import org.graphstream.graph.Edge;
import org.graphstream.graph.implementations.SingleGraph;

import java.awt.*;
import java.util.List;
import java.util.*;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.stream.Collectors;

import static org.example.Utils.printWithTID;


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

    public int getVerticesCount() {
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

    public Map<Integer, Integer> getColors() {
        Map<Integer, Integer>  colors = new HashMap<>();
        for (Node node : neighbors.keySet()) {
            colors.put(node.getValue(), node.getColorIndex());
        }
        return colors;
    }

    public Map<Integer, Integer> getWeights() {
        Map<Integer, Integer> weights = new HashMap<>(getVerticesCount());
        for (Node node : neighbors.keySet())
            weights.put(node.getValue(), node.getWeight());
        return weights;
    }

    public int getMaxColorIndex() {
        int maxColorIndex = 0;
        for (Node node : neighbors.keySet())
            if (neighbors.get(node).size() > maxColorIndex)
                maxColorIndex = neighbors.get(node).size();
        return maxColorIndex + 1;
    }

    public void setColor(int nodeValue, int colorIndex) {
        for(Node n : neighbors.keySet()) {
            if(n.getValue() == nodeValue)
                n.setColorIndex(colorIndex);
        }
    }

    private void computeNodeColor(Node node) {
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
                    computeNodeColor(node);
                });
            }
            achromaticNodes.removeAll(heavyNodes);
        }
        executorService.shutdown();
    }

    public void showGraph() {
        printWithTID("Colors: ");
        neighbors.keySet().forEach(node -> {
            printWithTID(node.getValue() + " has color " + node.getColorIndex());
        });

        printWithTID(" ");

        printWithTID("Neighbours: ");
        neighbors.forEach((node, nodes) -> {
            printWithTID(node.getValue() + " -> " + nodes.stream()
                    .map(Node::getValue)
                    .map(Objects::toString)
                    .reduce("", (a, b) -> a + " " + b));
        });

        printWithTID(" ");

        printWithTID("Neighbours (as colors): ");
        neighbors.forEach((node, nodes) -> {
            printWithTID(node.getValue() + ": " + node.getColorIndex() + " -> " + nodes.stream()
                    .map(Node::getColorIndex)
                    .map(Objects::toString)
                    .reduce("", (a, b) -> a + " " + b));
        });
    }

    void showGraphGUI() {
        System.setProperty("org.graphstream.ui", "swing");
        org.graphstream.graph.Graph graph = new SingleGraph("visual_graph");
        graph.setAttribute("ui.stylesheet", "node {size: 30px;}");
        graph.setAttribute("ui.antialias");
        graph.setAttribute("ui.stylesheet", "node {size: 30px;}");
        graph.setAttribute("ui.antialias");

        for (Node node : neighbors.keySet()) {
            if(node.getColorIndex() != -1) {
                org.graphstream.graph.Node n = graph.addNode(Integer.toString(node.getValue()));
                n.setAttribute("ui.style", "fill-color:" + getColor(node.getColorIndex()) + "; text-size: 20px;");
                n.setAttribute("ui.size", "3gu");
                n.setAttribute("ui.label", Integer.toString(node.getValue()));
                n.setAttribute("ui.class", "big");
            }
        }

        for (Node node : neighbors.keySet()) {
            for (Node node2 : neighbors.get(node)) {
                if (node2.getValue() < node.getValue()) continue;
                if (graph.getNode(Integer.toString(node.getValue())) != null && graph.getNode(Integer.toString(node2.getValue())) != null) {
//                    graph.addEdge(node.getValue() + Integer.toString(node2.getValue()), Integer.toString(node.getValue()), Integer.toString(node2.getValue()));
                    Edge e = graph.addEdge(Integer.toString(node.getValue()) + node2.getValue(), Integer.toString(node.getValue()), Integer.toString(node2.getValue()));
                    e.setAttribute("ui.style", "size: 3px;");
                }
            }
        }
        graph.display();
    }

    public boolean[][] toBooleanMatrix() {
        boolean[][] matrix = new boolean[getVerticesCount()][getVerticesCount()];
        for (int row = 0; row < getVerticesCount(); row++) {
            for (int column = 0; column < getVerticesCount(); column++) {
                matrix[row][column] = false;
            }
        }
        for (Node node : neighbors.keySet()) {
            for (Node neighbour : neighbors.get(node)) {
                matrix[node.getValue()][neighbour.getValue()] = true;
            }
        }
        return matrix;
    }

    private String getColor(int index) {
        return colorToHex(colors.get(index % colors.size()));
    }

    private static String colorToHex(Color color) {
        return String.format("#%02x%02x%02x", color.getRed(), color.getGreen(), color.getBlue());
    }
}
