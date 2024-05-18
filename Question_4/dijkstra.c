#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
int minDistance(int dist[], bool sptSet[], int len)
{
	int min = INT_MAX, min_index;
	for (int v = 0; v < len; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

// A utility function to print the constructed distance
// array
void printSolution(int dist[], int len)
{
	printf("Vertex \t\t Distance from Source\n");
	for (int i = 0; i < len; i++)
	{
		printf("%d \t\t\t\t %d\n", i, dist[i]); // \t is a tab (4 spaces)
	}
}

// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
bool isNegative(int row, int col, int graph[row][col])
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			if (graph[i][j] < 0)
				return true;
	return false;
}
// test to do
//  row != col of the matrix the matrix is not a squre
//  src < 0 or src >= row or src >= col
//  negative values in the matrix

void dijkstra(int row, int col, int graph[row][col], int src)
{
	printf("row: %d, col: %d\n src %d", row, col, src);
	if (row != col || src < 0 || src >= row || src >= col)
	{ // src can't be outside the matrix
		printf("Invalid source vertex\n");
		return;
	}
	if (isNegative(row, col, graph))
	{
		printf("Invalid graph\n");
		return;
	}

	int dist[row]; // The output array. dist[i] will hold the
					// shortest
	// distance from src to i

	bool sptSet[row]; // sptSet[i] will be true if vertex i is
						// included in shortest
	// path tree or shortest distance from src to i is
	// finalized

	// Initialize all distances as INFINITE and stpSet[] as
	// false
	for (int i = 0; i < row; i++)
		dist[i] = INT_MAX, sptSet[i] = false;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < row - 1; count++)
	{
		// Pick the minimum distance vertex from the set of
		// vertices not yet processed. u is always equal to
		// src in the first iteration.
		int u = minDistance(dist, sptSet, row);

		// Mark the picked vertex as processed
		sptSet[u] = true;

		// Update dist value of the adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < row; v++)

			// Update dist[v] only if is not in sptSet,
			// there is an edge from u to v, and total
			// weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	// print the constructed distance array
	printf("Shortest paths:");
	printSolution(dist, row);
}

#include <stdio.h>

void getInputForAdjacencyMatrix(int row, int col, int graph[row][col])
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			scanf("%d", &graph[i][j]);
		}
	}
}
int main()
{
	int row = -1, col = -1;

	printf("Enter the number of rows and columns of the adjacency matrix: ");
	if (scanf("%d%d", &row, &col) != 2 || row <= 0 || col <= 0)
	{
		printf("Invalid input: Number of rows and columns must be positive integers.\n");
		return -1;
	}

	int graph[row][col];
	printf("Enter the adjacency matrix:\n");
	getInputForAdjacencyMatrix(row, col, graph); // get the adjacency matrix from the user with scanf

	int src;

	printf("Enter the source vertex: ");
	if (scanf("%d", &src) != 1)
	{
		printf("Invalid input: Source vertex must be an integer.\n");
		return 1;
	}

	dijkstra(row, col, graph, src);

	return 0;
}
