#ifndef GRAPH_H
#define GRAPH_H

#include "algorithms.h"

// Function to create and initialize a graph
Graph* create_graph();
void free_graph(Graph* graph);

// Node and edge management
void add_node(Graph* graph, int id, const char* name, double lat, double lon);
void add_edge(Graph* graph, int from, int to, double distance, double time, double cost);

// Utility functions
void print_graph(Graph* graph);
void print_path_result(PathResult result, Graph* graph);
void free_path_result(PathResult result);

#endif
