#!/bin/bash

# Directory containing map files
MAP_DIR_GOOD="maps/good"
MAP_DIR_BAD="maps/bad"

# Function to run tests for a directory
run_tests() {
    local map_dir=$1

    # Iterate over all map files in the directory
    for map_file in "$map_dir"/*.cub; do
        # Display the map file name in blue
        echo -e "\e[34m$map_file\e[0m"
        
        # Run your program with the current map file and display the output
        ./cub3d "$map_file"
        
        # Add a separator between map outputs
        echo "--------------------------------------------"
    done
}

# Run tests for good maps
echo -e "\e[32mTesting for good maps:\e[0m"
run_tests "$MAP_DIR_GOOD"

# Run tests for bad maps
echo -e "\e[31mTesting for bad maps:\e[0m"
run_tests "$MAP_DIR_BAD"