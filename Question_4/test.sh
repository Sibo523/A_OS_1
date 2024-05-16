#!/bin/bash
# means that there's no edge between the two vertices

# I get the row col, 
# then get the input into the matrix 
# then I get the start vertex

# this test provide a valid input for the program, and it should return the shortest path from the start vertex to all other vertices
echo "4 4
0 10 2147483647 30
2147483647 0 50 2147483647
2147483647 2147483647 0 20
2147483647 2147483647 10 0
1" | ./dijkstra

# Run with a graph having too many edges
echo "3 3 
0 10 20 30
0" | ./dijkstra

# Run with a graph having negative weights
echo "3 3
0 10 -5
2147483647 0 20
2147483647 2147483647 0
0" | ./dijkstra

# Run with an invalid start vertex
echo "3 3
0 10 20
2147483647 0 20
2147483647 2147483647 0
-1" | ./dijkstra

# Run with zero vertices to exit
echo "0" | ./dijkstra