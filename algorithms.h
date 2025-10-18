#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#define MAX_NODES 100

// ---------- Struct Definitions ----------

// Represents a single road or connection between two nodes
typedef struct {
    int to;              // destination node index
    double distance;     // in km
    double time;         // in minutes or hours
    double cost;         // cost or weight
} Edge;

// Represents a single node (for A* heuristic)
typedef struct {
    double lat;          // latitude
    double lon;          // longitude
    char name[50];       // optional: name of the node
} Node;

// Graph structure holding adjacency matrix
typedef struct {
    int node_count;              // number of active nodes
    Node nodes[MAX_NODES];       // node metadata
    Edge* adj[MAX_NODES][MAX_NODES]; // adjacency matrix (pointer to Edge)
} Graph;

// PathResult stores the output of BFS, DFS, Dijkstra, or A*
typedef struct {
    int path[MAX_NODES];         // stores node indices in order
    int length;                  // number of nodes in path
    double total_distance;       // total km
    double total_time;           // total time
    double total_cost;           // total cost
} PathResult;

// ---------- Function Prototypes ----------

void add_edge(Graph* graph, int from, int to, double distance, double time, double cost);

PathResult bfs_shortest_path(Graph* graph, int start, int end);
PathResult dfs_path(Graph* graph, int start, int end);
PathResult dijkstra_shortest_path(Graph* graph, int start, int end, char metric);
PathResult astar_shortest_path(Graph* graph, int start, int end, char metric);

#endif
