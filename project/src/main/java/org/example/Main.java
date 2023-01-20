package org.example;
import mpi.MPI;


public class Main {
    /// change this values
    public static ApproachType approachType = ApproachType.MPI;
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
            worker(rank, numberOfProcesses);
        }

        MPI.Finalize();

    }

    private static void master(int numberOfProcesses) {
        boolean[][] matrix = graph.toBooleanMatrix();
        int[] weights = Utils.mapToIntArray(graph.getWeights());
        int[][] dataSent = new int[numberOfProcesses + 1][3];
        int maxColorIndex = graph.getMaxColorIndex();
        int[] colorIndexes = Utils.mapToIntArray(graph.getColors());
        int[] nodeCount = new int[]{graph.getVerticesCount()};

        int nodesPerProcess = nodeCount[0] / (numberOfProcesses - 1);
        int nodesForLastProcess = nodeCount[0] - nodesPerProcess * (numberOfProcesses - 2);
        int startingNodeIndex = 0, endingNodeIndex;

        for (int process = 1; process < numberOfProcesses - 1; process++) {
            //send number of vertices to all child processes
            MPI.COMM_WORLD.Issend(nodeCount, 0, 1, MPI.INT, process, process);
            //send neighbours of node k to all child processes
            for (int k = 0; k < nodeCount[0]; k++) {
                MPI.COMM_WORLD.Issend(matrix[k], 0, nodeCount[0], MPI.BOOLEAN, process, process);
            }
            //send all data needed to child processes
            endingNodeIndex = startingNodeIndex + nodesPerProcess - 1;
            dataSent[process][0] = startingNodeIndex;
            dataSent[process][1] = endingNodeIndex;
            dataSent[process][2] = maxColorIndex;
            MPI.COMM_WORLD.Issend(dataSent[process], 0, 3, MPI.INT, process, process);
            MPI.COMM_WORLD.Issend(colorIndexes, 0, nodeCount[0], MPI.INT, process, process);
            MPI.COMM_WORLD.Issend(weights, 0, nodeCount[0], MPI.INT, process, process);
            startingNodeIndex = endingNodeIndex + 1;
        }

        //special case for last child process
        int process = numberOfProcesses - 1;
        MPI.COMM_WORLD.Issend(nodeCount, 0, 1, MPI.INT, process, process);
        //send neighbours of node k to all child processes
        for (int k = 0; k < nodeCount[0]; k++) {
            MPI.COMM_WORLD.Issend(matrix[k], 0, nodeCount[0], MPI.BOOLEAN, process, process);
        }

        //send all data needed to child processes
        endingNodeIndex = startingNodeIndex + nodesForLastProcess - 1;
        dataSent[process][0] = startingNodeIndex;
        dataSent[process][1] = endingNodeIndex;
        dataSent[process][2] = maxColorIndex;
        MPI.COMM_WORLD.Issend(dataSent[process], 0, 3, MPI.INT, process, process);
        MPI.COMM_WORLD.Issend(colorIndexes, 0, nodeCount[0], MPI.INT, process, process);
        MPI.COMM_WORLD.Issend(weights, 0, nodeCount[0], MPI.INT, process, process);

        for (int i = 1; i < numberOfProcesses; i++) {
            MPI.COMM_WORLD.Recv(colorIndexes, 0, nodeCount[0], MPI.INT, i, i);
        }
        for (int i = 0; i < nodeCount[0]; i++) {
            graph.setColor(i, colorIndexes[i]);
        }
        int[] colors = Utils.mapToIntArray(graph.getColors());
        for (int i = 0; i < nodeCount[0]; i++) {
            System.out.println(colors[i]);
        }

        graph.showGraph();
    }

    private static void worker(int rank, int numberOfProcesses) {
        int[] nodeCount = new int[]{0};
        MPI.COMM_WORLD.Recv(nodeCount, 0, 1, MPI.INT, 0, rank);

        System.out.println(nodeCount[0]);

        boolean[][] graphMatrix = new boolean[nodeCount[0]][nodeCount[0]];
        for (int index = 0; index < nodeCount[0]; index++) {
            MPI.COMM_WORLD.Recv(graphMatrix[index], 0, nodeCount[0], MPI.BOOLEAN, 0, rank);
        }

        int[] dataReceived = new int[3];
        MPI.COMM_WORLD.Recv(dataReceived, 0, 3, MPI.INT, 0, rank);

        int[] colorIndexes = new int[nodeCount[0]];
        MPI.COMM_WORLD.Recv(colorIndexes, 0, nodeCount[0], MPI.INT, 0, rank);

        int[] weights = new int[nodeCount[0]];
        MPI.COMM_WORLD.Recv(weights, 0, nodeCount[0], MPI.INT, 0, rank);

        int currentNodeIndex;
        int iteration = 0;
        while (iteration < nodeCount[0]) {
            for (currentNodeIndex = dataReceived[0]; currentNodeIndex <= dataReceived[1]; currentNodeIndex++) {
                if (colorIndexes[currentNodeIndex] == -1) {
                    boolean isNodeHeaviest = true;
                    for (int neighbours = 0; neighbours < nodeCount[0]; neighbours++) {
                        if (neighbours != currentNodeIndex) {
                            if (graphMatrix[currentNodeIndex][neighbours] && colorIndexes[neighbours] == -1 && weights[neighbours] > weights[currentNodeIndex]) {
                                isNodeHeaviest = false;
                                break;
                            }
                        }
                    }
                    if (isNodeHeaviest) {
                        for (int alreadyAssignedColor = 0; alreadyAssignedColor < dataReceived[2]; alreadyAssignedColor++) {
                            boolean isColorAvailable = true;
                            //check if color is available (not taken by any neighbour)
                            for (int neighbours = 0; neighbours < nodeCount[0]; neighbours++) {
                                if (graphMatrix[currentNodeIndex][neighbours] && colorIndexes[neighbours] != -1 && alreadyAssignedColor == colorIndexes[neighbours]) {
                                    isColorAvailable = false;
                                    break;
                                }
                            }
                            if (isColorAvailable) {
                                colorIndexes[currentNodeIndex] = alreadyAssignedColor;
                                break;
                            }
                        }
                    }
                }

                for (int process = 1; process < numberOfProcesses; process++) {
                    if (process != rank)
                        MPI.COMM_WORLD.Issend(colorIndexes, 0, nodeCount[0], MPI.INT, process, process);
                }

                for (int process = 1; process < numberOfProcesses; process++) {
                    int[] localColorIndexes = new int[nodeCount[0]];
                    if (process != rank) {
                        MPI.COMM_WORLD.Recv(localColorIndexes, 0, nodeCount[0], MPI.INT, process, rank);
                        for (int nodeIndex = 0; nodeIndex < nodeCount[0]; nodeIndex++) {
                            if (colorIndexes[nodeIndex] == -1 && localColorIndexes[nodeIndex] != -1 && localColorIndexes[nodeIndex] < dataReceived[2] && localColorIndexes[nodeIndex] >= 0) {
                                colorIndexes[nodeIndex] = localColorIndexes[nodeIndex];
                            }
                        }
                    }
                }

                iteration++;
            }
            MPI.COMM_WORLD.Issend(colorIndexes, 0, nodeCount[0], MPI.INT, 0, rank);
        }
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