#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

Graph* create_graph() {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->num_nodes = 0;
    for (int i = 0; i < MAX_NODES; i++)
        for (int j = 0; j < MAX_NODES; j++)
            g->adj[i][j] = NULL;
    return g;
}

void add_node(Graph* graph, int id, const char* name, double lat, double lon) {
    if (graph->num_nodes >= MAX_NODES) {
        printf("Error: Cannot add more nodes (limit = %d)\n", MAX_NODES);
        return;
    }
    graph->nodes[id].id = id;
    strcpy(graph->nodes[id].name, name);
    graph->nodes[id].latitude = lat;
    graph->nodes[id].longitude = lon;
    graph->num_nodes++;
}

void add_edge(Graph* graph, int from, int to, double distance, double time, double cost) {
    if (from >= MAX_NODES || to >= MAX_NODES) {
        printf("Error: Invalid edge indices (%d, %d)\n", from, to);
        return;
    }

    // Allocate only once for both directions
    Edge* edge = (Edge*)malloc(sizeof(Edge));
    if (!edge) {
        printf("Memory allocation failed for edge (%d, %d)\n", from, to);
        return;
    }

    edge->to = to;
    edge->distance = distance;
    edge->time = time;
    edge->cost = cost;

    // Assign to both directions (bidirectional)
    graph->adj[from][to] = edge;
    graph->adj[to][from] = edge;
}


void print_graph(Graph* graph) {
    printf("\n=== GRAPH STRUCTURE ===\n");
    for (int i = 0; i < graph->num_nodes; i++) {
        printf("%d. %s -> ", i, graph->nodes[i].name);
        for (int j = 0; j < graph->num_nodes; j++) {
            if (graph->adj[i][j] != NULL) {
                printf("%s(%.0lfkm) ", graph->nodes[j].name, graph->adj[i][j]->distance);
            }
        }
        printf("\n");
    }
}

void free_graph(Graph* graph) {
    for (int i = 0; i < graph->num_nodes; i++) {
        for (int j = 0; j < graph->num_nodes; j++) {
            if (graph->adj[i][j] != NULL) {
                free(graph->adj[i][j]);
                graph->adj[i][j] = NULL;
            }
        }
    }
    free(graph);
}
