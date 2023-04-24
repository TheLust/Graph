//
// Created by Daniel on 24.04.2023.
//

#ifndef UTCPSI2_GRAPHMETHODS_H
#define UTCPSI2_GRAPHMETHODS_H

#endif //UTCPSI2_GRAPHMETHODS_H

#include <vector>
#include <algorithm>
#include <set>
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100;
const int INF = 1e9;

// Returns true if there is an Euler path starting from vertex u
bool hasEulerPath(int graph[MAXN][MAXN], int n, int u) {
    int degree = 0;
    for (int v = 0; v < n; v++) {
        if (graph[u][v] > 0) {
            degree++;
        }
    }
    return (degree % 2 == 1);
}

// Finds all Euler paths starting from vertex u
void findAllEulerPaths(int graph[MAXN][MAXN], int n, int u, vector<int>& path, vector<vector<int>>& paths) {
    path.push_back(u);
    if (path.size() == n) {
        paths.push_back(path);
    } else {
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0) {
                graph[u][v] = graph[v][u] = 0; // remove edge to prevent backtrack
                findAllEulerPaths(graph, n, v, path, paths);
                graph[u][v] = graph[v][u] = INF; // restore edge
            }
        }
    }
    path.pop_back();
}

// Wrapper function to find all Euler paths starting from vertex u
vector<vector<int>> getEulerPaths(int graph[MAXN][MAXN], int n, int u) {
    vector<vector<int>> paths;
    if (hasEulerPath(graph, n, u)) {
        vector<int> path;
        findAllEulerPaths(graph, n, u, path, paths);
    }
    return paths;
}

// Finds all Hamiltonian paths starting from vertex u
void findAllHamiltonPaths(int graph[MAXN][MAXN], int n, int u, vector<int>& path, vector<vector<int>>& paths) {
    path.push_back(u);
    if (path.size() == n) {
        paths.push_back(path);
    } else {
        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0) {
                bool visited = false;
                for (int w : path) {
                    if (w == v) {
                        visited = true;
                        break;
                    }
                }
                if (!visited) {
                    findAllHamiltonPaths(graph, n, v, path, paths);
                }
            }
        }
    }
    path.pop_back();
}

// Wrapper function to find all Hamiltonian paths starting from vertex u
vector<vector<int>> getHamiltonPaths(int graph[MAXN][MAXN], int n, int u) {
    vector<vector<int>> paths;
    vector<int> path;
    findAllHamiltonPaths(graph, n, u, path, paths);
    return paths;
}

// Computes the minimum cost Hamiltonian cycle in a complete weighted graph
int tsp(int graph[MAXN][MAXN], int n, vector<int>& path) {
    int minCost = INF;
    vector<int> vertices(n);
    for (int i = 0; i < n; i++) {
        vertices[i] = i;
    }
    do {
        int cost = 0;
        for (int i = 0; i < n - 1; i++) {
            cost += graph[vertices[i]][vertices[i+1]];
        }
        cost += graph[vertices[n-1]][vertices[0]];
        if (cost < minCost) {
            minCost = cost;
            path = vertices;
        }
    } while (next_permutation(vertices.begin() + 1, vertices.end()));
    return minCost;
}

int tsp_max(int graph[MAXN][MAXN], int n, vector<int>& path) {
    int start = 0;
    vector<bool> visited(n, false);
    visited[start] = true;
    path.push_back(start);
    int total_cost = 0;
    for (int i = 0; i < n - 1; i++) {
        int max_cost = INT_MIN; // changed to minimum integer value
        int max_vertex = -1;
        for (int j = 0; j < n; j++) {
            if (!visited[j] && graph[start][j] > max_cost) { // changed to > operator
                max_cost = graph[start][j];
                max_vertex = j;
            }
        }
        if (max_vertex == -1) {
            break;
        }
        visited[max_vertex] = true;
        path.push_back(max_vertex);
        total_cost += max_cost;
        start = max_vertex;
    }
    total_cost += graph[path.back()][path.front()]; // add cost of returning to start
    return total_cost;
}

int color_graph(int graph[MAXN][MAXN], int n, vector<int>& colors) {
    colors.resize(n, -1); // initialize all vertices to uncolored (-1)
    int num_colors = 0;
    for (int i = 0; i < n; i++) {
        vector<bool> used_colors(num_colors, false); // initialize all colors to unused
        for (int j = 0; j < n; j++) {
            if (graph[i][j] && colors[j] != -1) { // check adjacent vertices that are already colored
                used_colors[colors[j]] = true;
            }
        }
        int color = 0;
        while (color < num_colors && used_colors[color]) { // find the first unused color
            color++;
        }
        if (color == num_colors) { // no unused color found
            num_colors++;
        }
        colors[i] = color; // assign the vertex the first unused color
    }
    return num_colors; // return the number of colors used
}

int colorEdges(int graph[MAXN][MAXN], int vertexes, vector<int>& colors) {
    int chromaticIndex = 0;
    // Initialize all edges to have color 0
    for (int i = 0; i < vertexes; i++) {
        for (int j = i + 1; j < vertexes; j++) {
            if (graph[i][j] == 1) {
                colors.push_back(0);
            }
        }
    }
    // Color the edges
    for (int i = 0; i < vertexes; i++) {
        for (int j = i + 1; j < vertexes; j++) {
            if (graph[i][j] == 1) {
                // Find the colors of adjacent edges
                set<int> adjacentColors;
                for (int k = 0; k < colors.size(); k++) {
                    if (graph[i][k] == 1 && k != j) {
                        adjacentColors.insert(colors[k]);
                    }
                    if (graph[j][k] == 1 && k != i) {
                        adjacentColors.insert(colors[k]);
                    }
                }
                // Choose the first available color
                int color = 1;
                while (adjacentColors.find(color) != adjacentColors.end()) {
                    color++;
                }
                colors[i*(vertexes-1)+j-i-1] = color;
                chromaticIndex = max(chromaticIndex, color);
            }
        }
    }
    return chromaticIndex;
}

int parent[MAXN], rankk[MAXN]; // parent and rankk arrays for union-find

// find the parent of a vertex using union-find
int find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

// merge two sets using union-find
void merge(int x, int y) {
    int px = find(x), py = find(y);
    if (rankk[px] > rankk[py]) parent[py] = px;
    else parent[px] = py;
    if (rankk[px] == rankk[py]) rankk[py]++;
}

// Kruskal's algorithm
void kruskal(int graph[MAXN][MAXN], int vertexes) {
    // initialize parent and rankk arrays for union-find
    for (int i = 0; i < vertexes; i++) {
        parent[i] = i;
        rankk[i] = 0;
    }

    // create a list of all edges in the graph
    int edges = 0;
    pair<int, pair<int, int>> edgeList[MAXN*MAXN];
    for (int i = 0; i < vertexes; i++) {
        for (int j = 0; j < vertexes; j++) {
            if (graph[i][j] != INF) {
                edgeList[edges++] = {graph[i][j], {i, j}};
            }
        }
    }

    // sort the edges in non-decreasing order by weight
    sort(edgeList, edgeList+edges);

    // select edges for the minimum spanning tree
    int weight = 0;
    for (int i = 0; i < edges; i++) {
        int u = edgeList[i].second.first;
        int v = edgeList[i].second.second;
        int w = edgeList[i].first;
        if (find(u) != find(v)) {
            merge(u, v);
            cout << u << " - " << v << " : " << w << endl;
            weight += w;
        }
        if (weight == vertexes-1) break; // stop when we have added enough edges
    }

    cout << "Total weight: " << weight << endl;
}