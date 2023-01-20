package org.example;
import mpi.MPI;


public class Main {
    /// change this values
    public static ApproachType approachType = ApproachType.REGULAR;
    public static Graph graph = new Graph(10);

    public static void main(String[] args) {
        addEdges();

        if (approachType == ApproachType.MPI)
            runMPI(args);
        else
            runRegular();

        graph.showGraph();
    }

    private static void runRegular() {
        graph.colorGraph();
    }

    private static void runMPI(String[] args) {
        MPI.Init(args);

        int rank = MPI.COMM_WORLD.Rank();
        int numberOfProcesses = MPI.COMM_WORLD.Size();

        if (rank == 0) {
            master(numberOfProcesses);
        } else {
            worker(numberOfProcesses);
        }

        MPI.Finalize();

    }

    private static void master(int numberOfProcesses) {
        throw new UnsupportedOperationException("Not implemented yet"); // TODO
    }

    private static void worker(int numberOfProcesses) {
        throw new UnsupportedOperationException("Not implemented yet"); // TODO
    }

    private static void addEdges() {
        graph.addEdge(0, 2);
        graph.addEdge(0, 3);
        graph.addEdge(0, 5);
        graph.addEdge(1, 3);
        graph.addEdge(1, 4);
        graph.addEdge(1, 6);
        graph.addEdge(2, 4);
        graph.addEdge(2, 7);
        graph.addEdge(3, 8);
        graph.addEdge(4, 9);
        graph.addEdge(5, 6);
        graph.addEdge(5, 9);
        graph.addEdge(6, 7);
        graph.addEdge(7, 8);
        graph.addEdge(8, 9);
    }
}