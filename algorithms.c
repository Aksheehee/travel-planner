#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "algorithms.h"

// ---------- BFS ----------
PathResult bfs_shortest_path(Graph* graph, int start, int end) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES], parent[MAX_NODES];
    int front = 0, rear = 0;
    PathResult result = { .length = 0 };

    for (int i = 0; i < MAX_NODES; i++) parent[i] = -1;

    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int node = queue[front++];
        if (node == end) break;
        for (int j = 0; j < graph->node_count; j++) {
            if (graph->adj[node][j] && !visited[j]) {
                visited[j] = 1;
                parent[j] = node;
                queue[rear++] = j;
            }
        }
    }

    if (!visited[end]) return result; // no path found

    int path[MAX_NODES], len = 0;
    for (int v = end; v != -1; v = parent[v]) path[len++] = v;

    // Reverse path
    for (int i = 0; i < len; i++) result.path[i] = path[len - i - 1];
    result.length = len;

    // Calculate total weights
    result.total_distance = result.total_time = result.total_cost = 0;
    for (int i = 0; i < len - 1; i++) {
        Edge* e = graph->adj[result.path[i]][result.path[i + 1]];
        if (e) {
            result.total_distance += e->distance;
            result.total_time += e->time;
            result.total_cost += e->cost;
        }
    }
    return result;
}

// ---------- DFS ----------
int dfs_util(Graph* graph, int u, int end, int visited[], int path[], int* path_len) {
    visited[u] = 1;
    path[(*path_len)++] = u;
    if (u == end) return 1;

    for (int v = 0; v < graph->node_count; v++) {
        if (graph->adj[u][v] && !visited[v]) {
            if (dfs_util(graph, v, end, visited, path, path_len))
                return 1;
        }
    }
    (*path_len)--;
    return 0;
}

PathResult dfs_path(Graph* graph, int start, int end) {
    PathResult result = { .length = 0 };
    int visited[MAX_NODES] = {0}, path[MAX_NODES], len = 0;

    if (dfs_util(graph, start, end, visited, path, &len)) {
        result.length = len;
        for (int i = 0; i < len; i++) result.path[i] = path[i];
        result.total_distance = result.total_time = result.total_cost = 0;
        for (int i = 0; i < len - 1; i++) {
            Edge* e = graph->adj[result.path[i]][result.path[i + 1]];
            if (e) {
                result.total_distance += e->distance;
                result.total_time += e->time;
                result.total_cost += e->cost;
            }
        }
    }
    return result;
}

// ---------- Dijkstra ----------
double get_weight(Edge* e, char metric) {
    if (!e) return INFINITY;
    switch (metric) {
        case 'd': return e->distance;
        case 't': return e->time;
        case 'c': return e->cost;
        default: return e->distance;
    }
}

PathResult dijkstra_shortest_path(Graph* graph, int start, int end, char metric) {
    double dist[MAX_NODES];
    int parent[MAX_NODES];
    int visited[MAX_NODES] = {0};
    PathResult result = { .length = 0 };

    for (int i = 0; i < MAX_NODES; i++) {
        dist[i] = INFINITY;
        parent[i] = -1;
    }
    dist[start] = 0;

    for (int count = 0; count < graph->node_count - 1; count++) {
        double min = INFINITY;
        int u = -1;
        for (int v = 0; v < graph->node_count; v++) {
            if (!visited[v] && dist[v] < min) {
                min = dist[v];
                u = v;
            }
        }
        if (u == -1) break;
        visited[u] = 1;

        for (int v = 0; v < graph->node_count; v++) {
            Edge* e = graph->adj[u][v];
            if (e && !visited[v]) {
                double w = get_weight(e, metric);
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                }
            }
        }
    }

    if (dist[end] == INFINITY) return result;

    int path[MAX_NODES], len = 0;
    for (int v = end; v != -1; v = parent[v]) path[len++] = v;
    for (int i = 0; i < len; i++) result.path[i] = path[len - i - 1];
    result.length = len;

    result.total_distance = result.total_time = result.total_cost = 0;
    for (int i = 0; i < len - 1; i++) {
        Edge* e = graph->adj[result.path[i]][result.path[i + 1]];
        if (e) {
            result.total_distance += e->distance;
            result.total_time += e->time;
            result.total_cost += e->cost;
        }
    }
    return result;
}

// ---------- A* ----------
double heuristic(Node a, Node b, char metric) {
    double dx = a.lat - b.lat;
    double dy = a.lon - b.lon;
    double euclid = sqrt(dx * dx + dy * dy);
    switch (metric) {
        case 'd': return euclid * 111; // approx km/degree
        case 't': return euclid;
        case 'c': return euclid;
        default: return euclid;
    }
}

PathResult astar_shortest_path(Graph* graph, int start, int end, char metric) {
    double g[MAX_NODES], f[MAX_NODES];
    int parent[MAX_NODES];
    int visited[MAX_NODES] = {0};
    PathResult result = { .length = 0 };

    for (int i = 0; i < MAX_NODES; i++) {
        g[i] = INFINITY;
        f[i] = INFINITY;
        parent[i] = -1;
    }

    g[start] = 0;
    f[start] = heuristic(graph->nodes[start], graph->nodes[end], metric);

    while (1) {
        int u = -1;
        double minF = INFINITY;
        for (int i = 0; i < graph->node_count; i++) {
            if (!visited[i] && f[i] < minF) {
                minF = f[i];
                u = i;
            }
        }

        if (u == -1) break;
        if (u == end) break;

        visited[u] = 1;

        for (int v = 0; v < graph->node_count; v++) {
            Edge* e = graph->adj[u][v];
            if (e && !visited[v]) {
                double w = get_weight(e, metric);
                if (g[u] + w < g[v]) {
                    g[v] = g[u] + w;
                    f[v] = g[v] + heuristic(graph->nodes[v], graph->nodes[end], metric);
                    parent[v] = u;
                }
            }
        }
    }

    if (parent[end] == -1) return result;

    int path[MAX_NODES], len = 0;
    for (int v = end; v != -1; v = parent[v]) path[len++] = v;
    for (int i = 0; i < len; i++) result.path[i] = path[len - i - 1];
    result.length = len;

    result.total_distance = result.total_time = result.total_cost = 0;
    for (int i = 0; i < len - 1; i++) {
        Edge* e = graph->adj[result.path[i]][result.path[i + 1]];
        if (e) {
            result.total_distance += e->distance;
            result.total_time += e->time;
            result.total_cost += e->cost;
        }
    }
    return result;
}
