#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GraphMethods.h"

using namespace std;

// GLOBAL VARIABLES

int graph[100][100], vertexes;

// SHOW GRAPH

void ShowGraph()
{
    cout << "SHOW GRAPH: \n"
         << "GRAPH: \n";

    for (int i = 0; i < vertexes; i ++)
    {
        for (int j = 0; j < vertexes; j ++)
        {
            cout << graph[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    system("PAUSE");
}

// IMPORT FROM FILE

void ImportGraphFromFile()
{
    string file;
    cout << "IMPORT GRAPH FROM FILE\n"
         << "File name: ";
    cin >> file;
    file = "Files\\" + file;
    ifstream in(file);
    if (!in.good())
    {
        cout << "File doesn't exist!\n\n";
        system("PAUSE");
        in.close();
        return;
    }

    in >> vertexes;
    for (int i = 0; i < vertexes; i ++)
    {
        for (int j = 0; j < vertexes; j ++)
        {
            in >> graph[i][j];
        }
    }

    cout << "Graph imported.\n\n";
    system("PAUSE");
    in.close();
}

// DECLARE FROM KEYBOARD

void DeclareGraphFromKeyboard() {
    cout << "DECLARE GRAPH FROM KEYBOARD: \n"
         << "Number of vertexes: ";
    cin >> vertexes;
    cout << "The adjacency matrix:\n";
    for (int i = 0; i < vertexes; i ++)
    {
        for (int j = 0; j < vertexes; j ++)
        {
            cin >> graph[i][j];
        }
    }
    cout << "\n";
    ShowGraph();
}

// IMPORT MENU

void ImportMenu()
{
    int choice = -1;
    while (choice)
    {
        system("CLS");
        cout << "IMPORT MENU:\n"
             << "IMPORT GRAPH FROM FILE --------------- 1\n"
             << "DECLARE GRAPH FROM KEYBOARD ---------- 2\n"
             << "EXIT --------------------------------- 0\n"
             << "YOUR CHOICE: ";
        cin >> choice;
        system("CLS");
        switch (choice)
        {
            case 1:
            {
                ImportGraphFromFile();
                break;
            }

            case 2:
            {
                DeclareGraphFromKeyboard();
                break;
            }

            case 0:
            {
                break;
            }

            default:
            {
                cout<<"Invalid command!\n\n";
                system("PAUSE");
                break;
            }
        }
    }
}

void ShowEulerAndHamiltonianPaths()
{
    cout << "SHOW EULER AND HAMILTONIAN PATHS:\n"
         << "All EULER PATHS:\n";
    for (int i = 0; i < vertexes; i ++) {
        vector<vector<int>> paths = getEulerPaths(graph, vertexes, i);
        if (!paths.empty()) {
            cout << "\tEuler paths for vertex " << i << " :\n";
            for (auto path: paths) {
                cout << "\t\t";
                for (int v: path) {
                    cout << v << " ";
                }
                cout << "\n";
            }
        }
    }
    cout << "\nALL HAMILTONIAN PATHS:\n";
    for (int i = 0; i < vertexes; i ++) {
        vector<vector<int>> paths = getHamiltonPaths(graph, vertexes, i);
        if (!paths.empty()) {
            cout << "\tHamiltonian paths for vertex " << i << " :\n";
            for (auto path: paths) {
                cout << "\t\t";
                for (int v: path) {
                    cout << v << " ";
                }
                cout << "\n";
            }
        }
    }
    cout << "\n";
    system("PAUSE");
}

void TravelingSalesman()
{
    vector<int> path;
    int minCost = tsp(graph, vertexes, path);
    cout << "TRAVELING SALESMAN PROBLEM:\n"
         << "Minimum cost: " << minCost << "\n"
         << "Path: \n\t";
    for (int v : path) {
        cout << v << " ";
    }
    cout << path[0] << "\n\n";

    path.clear();
    minCost = tsp_max(graph, vertexes, path);
    cout << "Maximum cost: " << minCost << "\n"
                        << "Path: \n\t";
    for (int v : path) {
        cout << v << " ";
    }
    cout << path[0] << "\n\n";
    system("PAUSE");
}

void GraphColoring()
{
    vector<int> colors;
    int num_colors = color_graph(graph, vertexes, colors);
    cout << "GRAPH COLORING PROBLEM: \n"
         << "Minimum number of colors used for vertexes: " << num_colors << "\n"
         << "Vertex colors:" << "\n";
    for (int i = 0; i < vertexes; i++) {
        cout << "Vertex " << i << ": Color " << colors[i] << "\n";
    }
    colors.clear();
    int chromaticIndex = colorEdges(graph, vertexes, colors);
    // Print the chromatic index
    cout << "\nMinimum number of colors for edges: " << chromaticIndex << "\n";
    for (int i = 0; i < vertexes; i++) {
        for (int j = i + 1; j < vertexes; j++) {
            if (graph[i][j] == 1) {
                cout << "\t(" << i << "," << j << "): " << colors[i*(vertexes-1)+j-i-1] << "\n";
            }
        }
    }
    cout << "\n";
    system("PAUSE");
}

void KruskalAlgorithm()
{
    cout << "KRUSKAL ALGORITHM: \n";
    for (int i = 0; i < vertexes; i++)
    {
        for (int j = 0; j < vertexes; j++)
        {
            if (graph[i][j] == 0)
                graph[i][j] = INF; // set 0 weights to infinity
        }
    }
    kruskal(graph, vertexes);
    cout << "\n";
    system("PAUSE");
}

// MENU

void Menu()
{
    int choice = -1;
    while (choice)
    {
        system("CLS");
        cout << "MENU:\n"
             << "IMPORT GRAPH ------------------------- 1\n"
             << "SHOW GRAPH --------------------------- 2\n"
             << "SHOW EULER AND HAMILTON PATHS -------- 3\n"
             << "TRAVELING SALESMAN PROBLEM ----------- 4\n"
             << "THE GRAPH COLORING PROBLEM ----------- 5\n"
             << "KRUSKAL'S ALGORITHM ------------------ 6\n"
             << "EXIT --------------------------------- 0\n"
             << "YOUR CHOICE: ";
        cin >> choice;
        system("CLS");
        switch (choice) {
            case 1: {
                ImportMenu();
                break;
            }

            case 2: {
                ShowGraph();
                break;
            }

            case 3: {
                ShowEulerAndHamiltonianPaths();
                break;
            }

            case 4:
            {
                TravelingSalesman();
                break;
            }

            case 5:
            {
                GraphColoring();
                break;
            }

            case 6:
            {
                KruskalAlgorithm();
                break;
            }

            case 0:
            {
                cout << "Program finished!\n";
                break;
            }

            default:
            {
                cout<<"Invalid command!\n\n";
                system("PAUSE");
                break;
            }
        }
    }
}

// MAIN FUNCTION

int main()
{
    Menu();
    return 0;
}