#include <stdio.h>
#include "graph.h"
#include "algorithms.h"




void initialize_sample_graph(Graph* graph) {
    // Add nodes (cities) - 10 major Indian cities
    add_node(graph, 0, "Delhi", 28.6139, 77.2090);
    add_node(graph, 1, "Mumbai", 19.0760, 72.8777);
    add_node(graph, 2, "Bangalore", 12.9716, 77.5946);
    add_node(graph, 3, "Kolkata", 22.5726, 88.3639);
    add_node(graph, 4, "Chennai", 13.0827, 80.2707);
    add_node(graph, 5, "Hyderabad", 17.3850, 78.4867);
    add_node(graph, 6, "Ahmedabad", 23.0225, 72.5714);
    add_node(graph, 7, "Pune", 18.5204, 73.8567);
    add_node(graph, 8, "Jaipur", 26.9124, 75.7873);
    add_node(graph, 9, "Lucknow", 26.8467, 80.9462);
    
    // Add edges with distance(km), time(hours), cost(INR)
    // Conversion rate: 1 USD = 83 INR (approximate)
    
    // Delhi connections
    add_edge(graph, 0, 1, 1400, 2.5, 12450);   // Delhi-Mumbai (150 USD = 12450 INR)
    add_edge(graph, 0, 3, 1300, 2.0, 9960);    // Delhi-Kolkata (120 USD = 9960 INR)
    add_edge(graph, 0, 5, 1250, 2.2, 10750);   // Delhi-Hyderabad
    add_edge(graph, 0, 6, 950, 1.8, 8300);     // Delhi-Ahmedabad
    add_edge(graph, 0, 8, 280, 0.7, 2490);     // Delhi-Jaipur
    add_edge(graph, 0, 9, 550, 1.2, 4980);     // Delhi-Lucknow
    
    // Mumbai connections
    add_edge(graph, 1, 2, 1000, 1.5, 8300);    // Mumbai-Bangalore (100 USD = 8300 INR)
    add_edge(graph, 1, 5, 700, 1.0, 6640);     // Mumbai-Hyderabad (80 USD = 6640 INR)
    add_edge(graph, 1, 6, 530, 1.0, 5810);     // Mumbai-Ahmedabad
    add_edge(graph, 1, 7, 150, 0.5, 2075);     // Mumbai-Pune
    
    // Bangalore connections
    add_edge(graph, 2, 4, 350, 0.8, 4150);     // Bangalore-Chennai (50 USD = 4150 INR)
    add_edge(graph, 2, 5, 500, 0.7, 4980);     // Bangalore-Hyderabad (60 USD = 4980 INR)
    add_edge(graph, 2, 7, 840, 1.3, 7470);     // Bangalore-Pune
    
    // Kolkata connections
    add_edge(graph, 3, 4, 1600, 2.2, 14940);   // Kolkata-Chennai (180 USD = 14940 INR)
    add_edge(graph, 3, 9, 980, 1.8, 9130);     // Kolkata-Lucknow
    
    // Chennai connections
    add_edge(graph, 4, 5, 600, 1.0, 5810);     // Chennai-Hyderabad (70 USD = 5810 INR)
    
    // Hyderabad connections
    add_edge(graph, 5, 7, 560, 1.0, 5810);     // Hyderabad-Pune
    
    // Ahmedabad connections
    add_edge(graph, 6, 7, 660, 1.2, 6640);     // Ahmedabad-Pune
    add_edge(graph, 6, 8, 650, 1.3, 6640);     // Ahmedabad-Jaipur
    
    // Pune connections
    add_edge(graph, 7, 8, 1160, 2.0, 9960);    // Pune-Jaipur
    
    // Jaipur connections
    add_edge(graph, 8, 9, 570, 1.1, 4980);     // Jaipur-Lucknow
    
    // Additional cross-connections for better route options
    add_edge(graph, 1, 8, 1150, 2.0, 10750);   // Mumbai-Jaipur
    add_edge(graph, 2, 9, 1850, 3.0, 16600);   // Bangalore-Lucknow
    add_edge(graph, 3, 5, 1200, 2.1, 11200);   // Kolkata-Hyderabad
    add_edge(graph, 4, 7, 1150, 1.9, 10750);   // Chennai-Pune
}

void display_menu() {
    printf("\n=== TRAVEL PLANNER USING GRAPH ===\n");
    printf("1. Display Graph Structure\n");
    printf("2. Find Path using BFS (Fewest Stops)\n");
    printf("3. Find Path using DFS\n");
    printf("4. Find Shortest Path using Dijkstra\n");
    printf("5. Find Path using A* Algorithm\n");
    printf("6. Compare All Algorithms\n");
    printf("7. Exit\n");
    printf("Choose an option: ");
}

int main() {
    Graph* graph = create_graph();
    initialize_sample_graph(graph);
    
    int choice;
    int start, end;
    char metric;   // ✅ declare metric once here
    
    do {
        display_menu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                print_graph(graph);
                break;
            }
                
            case 2: {
                printf("Enter start node (0-5): ");
                scanf("%d", &start);
                printf("Enter end node (0-5): ");
                scanf("%d", &end);
                printf("\nBFS Path (Fewest Stops):\n");
                PathResult bfs_result = bfs_shortest_path(graph, start, end);
                print_path_result(bfs_result, graph);
                free_path_result(bfs_result);
                break;
            }
                
            case 3: {
                printf("Enter start node (0-5): ");
                scanf("%d", &start);
                printf("Enter end node (0-5): ");
                scanf("%d", &end);
                printf("\nDFS Path:\n");
                PathResult dfs_result = dfs_path(graph, start, end);
                print_path_result(dfs_result, graph);
                free_path_result(dfs_result);
                break;
            }
                
            case 4: {
                printf("Enter start node (0-5): ");
                scanf("%d", &start);
                printf("Enter end node (0-5): ");
                scanf("%d", &end);
                printf("Choose metric (d=distance, t=time, c=cost): ");
                scanf(" %c", &metric);
                printf("\nDijkstra Shortest Path:\n");
                PathResult dijkstra_result = dijkstra_shortest_path(graph, start, end, metric);
                print_path_result(dijkstra_result, graph);
                free_path_result(dijkstra_result);
                break;
            }
                
            case 5: {
                printf("Enter start node (0-5): ");
                scanf("%d", &start);
                printf("Enter end node (0-5): ");
                scanf("%d", &end);
                printf("Choose metric (d=distance, t=time, c=cost): ");
                scanf(" %c", &metric);
                printf("\nA* Algorithm Path:\n");
                PathResult astar_result = astar_shortest_path(graph, start, end, metric);
                print_path_result(astar_result, graph);
                free_path_result(astar_result);
                break;
            }
                
            case 6: {
                printf("Enter start node (0-5): ");
                scanf("%d", &start);
                printf("Enter end node (0-5): ");
                scanf("%d", &end);
                
                printf("\n=== COMPARING ALL ALGORITHMS ===\n");
                
                printf("\n1. BFS (Fewest Stops):\n");
                PathResult bfs_comp = bfs_shortest_path(graph, start, end);
                print_path_result(bfs_comp, graph);
                
                printf("\n2. DFS:\n");
                PathResult dfs_comp = dfs_path(graph, start, end);
                print_path_result(dfs_comp, graph);
                
                printf("\n3. Dijkstra (Shortest Distance):\n");
                PathResult dijkstra_comp = dijkstra_shortest_path(graph, start, end, 'd');
                print_path_result(dijkstra_comp, graph);
                
                printf("\n4. A* (Optimized):\n");
                PathResult astar_comp = astar_shortest_path(graph, start, end, 'd');
                print_path_result(astar_comp, graph);
                
                free_path_result(bfs_comp);
                free_path_result(dfs_comp);
                free_path_result(dijkstra_comp);
                free_path_result(astar_comp);
                break;
            }
                
            case 7: {
                printf("Exiting...\n");
                break;
            }
                
            default: {
                printf("Invalid choice! Please try again.\n");
            }
        }
    } while (choice != 7);
    
    free_graph(graph);
    return 0;
}

