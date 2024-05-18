# Function to run dijkstra with input from stdin and capture output
run_dijkstra() {
    # Run dijkstra and capture its output
    output=$(./dijkstra)

    # Print the output for debugging (optional)
    echo "$output"

    # Validate the output (example: check if it contains "Shortest paths:")
    if [[ $output == *"Shortest paths:"* ]]; then
        echo "Test passed: Shortest paths found "
        for ((i=0; i<150; i++)); do
            echo -n "*"
        done
        echo  # Add a newline at the end

    else
        echo "Program existed: Shortest paths not found "
        for ((i=0; i<150; i++)); do
            echo -n "*"
        done
        echo  # Add a newline at the end
    fi
}

# Test case 1: Valid input for the program should run on all lines that doesn't exit
echo "3 3
0 10 21
4 0 17
19 3 0
1" | run_dijkstra

# Test case 2: Graph with too many edges
echo "3 3 
0 10 20 30 20 30 50 2 3 4 
0" | run_dijkstra

# Test case 3: Graph with negative weights
echo "3 3
0 10 -5
15 0 20
7 9 0
0" | run_dijkstra

# Test case 4: Invalid start vertex
echo "3 3
0 10 20
15 0 20
7 9 0
-1" | run_dijkstra

# Test case 5: Zero vertices (exit)
echo "-2 -3" | run_dijkstra

# Test case 6: non int source (exit)
echo "3 3
0 10 20
15 0 20
7 9 0
A" | run_dijkstra